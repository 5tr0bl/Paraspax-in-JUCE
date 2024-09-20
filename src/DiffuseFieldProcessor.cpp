/*
  ==============================================================================

    DiffuseFieldProcessor.cpp
    Created: 30 Jan 2024 11:10:34am
    Author:  Micha

  ==============================================================================
*/

#include "DiffuseFieldProcessor.h"

DiffuseFieldProcessor::DiffuseFieldProcessor()
{
    fs = 48000.f; // create setter to call in prepareToPlay() !!!
    delay = 0;

    dfpDelay = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    //dfpDelay.reset();
    dfpDelay.setMaximumDelayInSamples(48000); // 1 sec max delay
    dfpDelay.setDelay(delay + bnfLatency);

    delayLineLP = std::make_unique<DelayLineLP>();

    dfpDelayTIPS = DelayLineTIPS();
    dfpDelayTIPS.setMaximumDelayInSamples(2 * fs); // 2 sec max delay
    dfpDelayTIPS.setDelay(delay + bnfLatency);

    dfpInitialized = false;
}

DiffuseFieldProcessor::~DiffuseFieldProcessor()
{
}

/* sampleRate gets passed ONCE upon calling constructor */
// binRev and weighting function should already have been provided by JSON import
void DiffuseFieldProcessor::init(juce::dsp::ProcessSpec& spec, float mixingTime, float sampleRate)
{
    dfpInitialized = false;
    fs = sampleRate;
    
    int mixingTimeInSamples = (int)((mixingTime / 1000) * spec.sampleRate); // mixing time gets passed in as milliseconds
    mixingTimeInSamples *= 2; // see synthesizeBRIR.m l.37
    mixingTimeInSamples = inverseWeightingFunc.getNumSamples(); // this seems to work better, matches Johannes' value
    
    int binRevNumSamples = binRevBuffer.getNumSamples();
    int binRevExcerptNumSamples = binRevNumSamples - mixingTimeInSamples;

    juce::AudioBuffer<float> binRevWeighted(binRevBuffer.getNumChannels(), binRevNumSamples);
    binRevWeighted.copyFrom(0, 0, binRevBuffer, 0, 0, binRevNumSamples);
    binRevWeighted.copyFrom(1, 0, binRevBuffer, 1, 0, binRevNumSamples);

    //saveAudioBufferAsJsonStereo(binRevWeighted, "binRevWeightedPre.json");

    // second recommendation
    for (int channel = 0; channel < binRevWeighted.getNumChannels(); ++channel) {
        // Get pointers to channel data for efficient memory access
        float* binRevWeightedData = binRevWeighted.getWritePointer(channel);
        const float* binRevBufferData = binRevBuffer.getReadPointer(channel);
        const float* inverseWeightingFuncData = inverseWeightingFunc.getReadPointer(0);

        for (int sample = 0; sample < mixingTimeInSamples; ++sample) {
            // Apply weighting function and copy to binRevWeighted
            binRevWeightedData[sample] = binRevBufferData[sample] * inverseWeightingFuncData[sample];
        }
        // Copy remaining samples without weighting
        std::memcpy(binRevWeightedData + mixingTimeInSamples, binRevBufferData + mixingTimeInSamples, (binRevNumSamples - mixingTimeInSamples) * sizeof(float));
    }

    //saveAudioBufferAsJsonStereo(binRevBuffer, "binRevBuffer.json");
    //saveAudioBufferAsJsonStereo(binRevWeighted, "binRevWeighted.json");
    //saveAudioBufferAsJSON(inverseWeightingFunc, "wfInv.json");
    
    // temporary buffer's ownership is moved to convolver
    convolver.loadImpulseResponse(std::move(binRevWeighted), spec.sampleRate,
                                  juce::dsp::Convolution::Stereo::yes,
                                  juce::dsp::Convolution::Trim::no, 
                                  juce::dsp::Convolution::Normalise::no);
    convolver.reset();
    convolver.prepare(spec);
    //auto irs = convolver.getCurrentIRSize(); // debug purpose
    //int latency = convolver.getLatency();

    dfpDelay.reset();
    dfpDelay.setMaximumDelayInSamples(spec.sampleRate); // 1 sec max delay
    dfpDelay.setDelay(delay + bnfLatency);
    dfpDelay.prepare(spec);

    delayLineLP->initFilter(48000);
    delayLineLP->reset();
    delayLineLP->setMaximumDelayInSamples(spec.sampleRate);
    delayLineLP->prepare(spec);

    /*
    dfpDelayTIPS.reset();
    dfpDelayTIPS.setMaximumDelayInSamples(2 * spec.sampleRate); // 2 sec max delay
    dfpDelayTIPS.prepare(spec);
    */

    currentDelaySmoothed.reset(spec.sampleRate, 0.01);
    setSmoothedDelayTimeInSamples(delay, spec.sampleRate, true);

    dfpInitialized = true;
}

// inverted weighting function already applied in init()
void DiffuseFieldProcessor::process(juce::AudioBuffer<float>& outputBuffer)
{
    if (dfpInitialized)
    {
        outputBuffer.clear();

        // inputBuffer has been filled prior within PluginProcessor.processBlock()
        juce::dsp::AudioBlock<float> blockToProcess = juce::dsp::AudioBlock<float>(inputBuffer);
        juce::dsp::ProcessContextReplacing<float> context(blockToProcess);
        delayLineLP->process(context, currentDelaySmoothed);
        convolver.process(context);
        //dfpDelayTIPS.process(context, currentDelaySmoothed);
        //dfpDelay.process(context);

        outputBuffer.addFrom(0, 0, inputBuffer, 0, 0, inputBuffer.getNumSamples());
        outputBuffer.addFrom(1, 0, inputBuffer, 1, 0, inputBuffer.getNumSamples());
    }
}

bool DiffuseFieldProcessor::isInitialized()
{
    return dfpInitialized;
}

void DiffuseFieldProcessor::setDelay(float newDelay)
{
    //std::lock_guard<std::mutex> lock(diffuseFieldProcessorMutex);
    
    newDelay += bnfLatency;
    if(newDelay != delay)
        dfpDelay.setDelay(newDelay);
}

void DiffuseFieldProcessor::setSmoothedDelayTimeInSamples(float delayTimeInSamples, double sampleRate, bool force)
{
    // set target value for SmoothedValue, force if you want to skip the ramp
    currentDelaySmoothed.setValue(jmax(0.f,(delayTimeInSamples + bnfLatency)), force);
}

/* update delay in the same way as in DelayProcessor */
void DiffuseFieldProcessor::setDelayByDistance(float distance)
{
    //No need for close distance limiter here
    /*
    if (std::abs(distance) < 0.15f) {
        distance = (distance > 0) ? 0.15f : -0.15f;
    }
    */

    float delayInSamples = distance * (fs / SONIC_SPEED); // SONIC_SPEED defined in _common.h
    setSmoothedDelayTimeInSamples(delayInSamples, fs, false);
    //setDelay(delayInSamples);
}

void DiffuseFieldProcessor::saveAudioBufferAsJsonStereo(const juce::AudioBuffer<float>& buffer, const juce::String& fileName)
{
    // Create JSON objects for left and right channels
    juce::DynamicObject::Ptr leftChannelData = new juce::DynamicObject();
    juce::DynamicObject::Ptr rightChannelData = new juce::DynamicObject();

    // Create JSON arrays for left and right channels
    juce::Array<juce::var> leftChannelArray;
    juce::Array<juce::var> rightChannelArray;

    // Populate the JSON arrays with samples from respective channels
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        leftChannelArray.add(buffer.getSample(0, sample)); // Left channel
        rightChannelArray.add(buffer.getSample(1, sample)); // Right channel
    }

    // Add left and right channel arrays to their respective JSON objects
    leftChannelData->setProperty("leftChannel", leftChannelArray);
    rightChannelData->setProperty("rightChannel", rightChannelArray);

    // Convert the JSON objects to JSON format
    juce::MemoryOutputStream leftChannelStream;
    juce::MemoryOutputStream rightChannelStream;
    juce::JSON::writeToStream(leftChannelStream, juce::var(leftChannelData));
    juce::JSON::writeToStream(rightChannelStream, juce::var(rightChannelData));

    juce::String directoryPath = "C:\\Users\\Micha\\source\\repos\\SPARTA-master\\audio_plugins\\_SPARTA_binauraliser_nf_\\Python\\Measurements\\binRevDumpsInJuce";
    juce::File jsonFile(directoryPath + juce::File::getSeparatorString() + fileName);
    if (jsonFile.existsAsFile())
        jsonFile.deleteFile();

    // Write left channel data to the file
    jsonFile.appendText("Left Channel:\n" + leftChannelStream.toString() + "\n");

    // Write right channel data to the file
    jsonFile.appendText("Right Channel:\n" + rightChannelStream.toString());
}

void DiffuseFieldProcessor::saveAudioBufferAsJSON(const juce::AudioBuffer<float>& buffer, const juce::String& fileName)
{
    // Create a JSON array to store the audio samples
    juce::Array<juce::var> samplesArray;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        juce::Array<float> channelData;
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData.add(buffer.getSample(channel, sample));
        }
        samplesArray.addArray(channelData);
    }

    // Convert samplesArray to JSON format
    juce::MemoryOutputStream outputStream;
    juce::JSON::writeToStream(outputStream, samplesArray);

    // Write the JSON data to a file
    juce::String directoryPath = "C:\\Users\\Micha\\source\\repos\\SPARTA-master\\audio_plugins\\_SPARTA_binauraliser_nf_\\Python\\Measurements\\binRevDumpsInJuce";
    juce::File jsonFile(directoryPath + juce::File::getSeparatorString() + fileName);

    if (jsonFile.existsAsFile())
        jsonFile.deleteFile();
    jsonFile.appendText(outputStream.toString());
}