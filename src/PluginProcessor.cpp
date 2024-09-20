/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Michael McCrea, Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h" 

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(1), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(2), true)),
    /**
    * The SPARTA code handled the parameters without an AudioProcessorValueTreeState
    * so this here will be handling the aditional parameters (VAE positioning & gain parameters)
    * Part of the reason to do this is to create a state where the XY Pad does not dominate the Sliders and vice versa
    * This will also make it easier to be automated by a DAW
    */
    apvts(*this, nullptr, "positionParams", {
        // Parameter layout
        std::make_unique<AudioParameterFloat>("srcPosX", "Source Position X", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("srcPosY", "Source Position Y", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("srcPosZ", "Source Position Z", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("lisPosX", "Listener Position X", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("lisPosY", "Listener Position Y", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("lisPosZ", "Listener Position Z", juce::NormalisableRange<float>(0.f, 80.f), 0.f),
        std::make_unique<AudioParameterFloat>("specGain", "Specular Sound Gain", juce::NormalisableRange<float>(-60.f, 6.f), 0.f),
        std::make_unique<AudioParameterFloat>("diffGain", "Diffuse Sound Gain", juce::NormalisableRange<float>(-60.f, 6.f), 0.f)
     })
{
	// add listeners to the apvts params
    apvts.addParameterListener("srcPosX", this);
    apvts.addParameterListener("srcPosY", this);
    apvts.addParameterListener("srcPosZ", this);
    apvts.addParameterListener("lisPosX", this);
    apvts.addParameterListener("lisPosY", this);
    apvts.addParameterListener("lisPosZ", this);
    apvts.addParameterListener("specGain", this);
    apvts.addParameterListener("diffGain", this);
    
    binauraliserNF_create(&hBin);

    /* specify here on which UDP port number to receive incoming OSC messages */
    setOscPortID(DEFAULT_OSC_PORT);

    refreshWindow = true;
    startTimer(TIMER_PROCESSING_RELATED, 25); // original interval == 80
    /* Far field distance threshold plus head room to firmly clear it with UI sliders. */
    nfThresh = binauraliserNF_getNearfieldLimit_m(hBin);
    ffThresh = binauraliserNF_getFarfieldThresh_m(hBin);
    ffHeadroom = binauraliserNF_getFarfieldHeadroom(hBin);
    upperDistRange = ffThresh * ffHeadroom;
    upperDistRange = 60.f;

    mixingTime = brirSpecGain = 0.f;
    psxLoaded = false;
    idleLoadingConfig = false;
    updateDelayProcessorParams = false;
    updateRoomDims = false;
    updateXyPadPosition = false;
    dfpEnabled = true;
    startEndArray.resize(2, std::vector<int>(NUM_DELAY_PROCESSORS));
    listenerPositionCurrent = std::make_unique<Vector3D<float>>(0, 0, 0);
    listenerPositionInit = std::make_unique<Vector3D<float>>(0, 0, 0);
    sourcePositionCurrent = std::make_unique<Vector3D<float>>(0, 0, 0);
    sourcePositionInit = std::make_unique<Vector3D<float>>(0, 0, 0);
    roomDims = std::make_unique<Vector3D<float>>(0, 0, 0);

    specularGain = diffuseGain = 1.f;
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);

    apvts.removeParameterListener("srcPosX", this);
    apvts.removeParameterListener("srcPosY", this);
    apvts.removeParameterListener("srcPosZ", this);
    apvts.removeParameterListener("lisPosX", this);
    apvts.removeParameterListener("lisPosY", this);
    apvts.removeParameterListener("lisPosZ", this);
    apvts.removeParameterListener("specGain", this);
    apvts.removeParameterListener("diffGain", this);
    
	binauraliserNF_destroy(&hBin);
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* This is the use case for the Max Msp patch used for the listening test */
    if (message.size() == 3) {
        if (message.getAddressPattern().toString().compare("/ypr") == 0)
        {
            if (message[0].isFloat32())
                binauraliser_setYaw(hBin, message[0].getFloat32());
            if (message[1].isFloat32())
                binauraliser_setPitch(hBin, message[1].getFloat32());
            if (message[2].isFloat32())
                binauraliser_setRoll(hBin, message[2].getFloat32());
            return;
        }
        if (message.getAddressPattern().toString().compare("/lis_xyz") == 0)
        {
            auto* xLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosX"));
            auto* yLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosY"));
            auto* zLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosZ"));
            
            if (message[0].isFloat32())
            {
                auto scaledLisX = jmap(message[0].getFloat32(), 0.f, roomDims->x, 0.f, 1.f);
                xLisParam->setValueNotifyingHost(scaledLisX);
            }
            if (message[1].isFloat32())
            {
                auto scaledLisY = jmap(message[1].getFloat32(), 0.f, roomDims->y, 0.f, 1.f);
                yLisParam->setValueNotifyingHost(scaledLisY);
            }
            if (message[2].isFloat32())
            {
                auto scaledLisZ = jmap(message[2].getFloat32(), 0.f, roomDims->z, 0.f, 1.f);
                zLisParam->setValueNotifyingHost(scaledLisZ);
            }
            return;
        }
    }

    /* ParaSpaX 6-DOF array \6dof[6], position followed by orientation */
    if (message.size() == 6 && message.getAddressPattern().toString().compare("/6dof") == 0) {
        auto* xLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosX"));
        auto* yLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosY"));
        auto* zLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosZ"));
        if (message[0].isFloat32())
        {
            xLisParam->setValueNotifyingHost(message[0].getFloat32());
        }
        if (message[1].isFloat32())
        {
            yLisParam->setValueNotifyingHost(message[1].getFloat32());
        }
        if (message[2].isFloat32())
        {
            zLisParam->setValueNotifyingHost(message[2].getFloat32());
        }
        if (message[3].isFloat32())
            binauraliser_setYaw(hBin, message[3].getFloat32());
        if (message[4].isFloat32())
            binauraliser_setPitch(hBin, message[4].getFloat32());
        if (message[5].isFloat32())
            binauraliser_setRoll(hBin, message[5].getFloat32());
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw") == 0)
        binauraliser_setYaw(hBin, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/pitch") == 0)
        binauraliser_setPitch(hBin, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/roll") == 0)
        binauraliser_setRoll(hBin, message[0].getFloat32());
    else if (message.getAddressPattern().toString().compare("/x_lis") == 0)
    {
        auto* xLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosX"));
        xLisParam->setValueNotifyingHost(message[0].getFloat32());
    }
    else if (message.getAddressPattern().toString().compare("/y_lis") == 0)
    {
        auto* yLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosY"));
        yLisParam->setValueNotifyingHost(message[0].getFloat32());
    }
    else if (message.getAddressPattern().toString().compare("/z_lis") == 0)
    {
        auto* zLisParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosZ"));
        zLisParam->setValueNotifyingHost(message[0].getFloat32());
    }    
}

/*
void PluginProcessor::setParameter (int index, float newValue)
{
    // standard parameters 
    if(index < k_NumOfParameters){
        switch (index) {
            case k_srcPosX:         
                //auto* srcPosXParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("srcPosX"));
                //srcPosXParam->setValue(newValue);
                break;
            case k_srcPosY:         break;
            case k_srcPosZ:         break;
            case k_lisPosX:         listenerPositionCurrent->x = newValue; break;
            case k_lisPosY:         listenerPositionCurrent->y = newValue; break;
            case k_lisPosZ:         listenerPositionCurrent->z = newValue; break;
            case k_enableRotation:  binauraliser_setEnableRotation(hBin, (int)(newValue + 0.5f)); break;
            case k_useRollPitchYaw: binauraliser_setRPYflag(hBin, (int)(newValue + 0.5f)); break;
            case k_yaw:             binauraliser_setYaw(hBin, (newValue - 0.5f) * 360.0f); break;
            case k_pitch:           binauraliser_setPitch(hBin, (newValue - 0.5f) * 180.0f); break;
            case k_roll:            binauraliser_setRoll(hBin, (newValue - 0.5f) * 180.0f); break;
            case k_flipYaw:         binauraliser_setFlipYaw(hBin, (int)(newValue + 0.5f));  break;
            case k_flipPitch:       binauraliser_setFlipPitch(hBin, (int)(newValue + 0.5f)); break;
            case k_flipRoll:        binauraliser_setFlipRoll(hBin, (int)(newValue + 0.5f)); break;
            case k_numInputs:       binauraliser_setNumSources(hBin, (int)(newValue*(float)(MAX_NUM_INPUTS) + 0.5)); break;
        }
    }
    // source direction parameters 
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        switch (index % 3) {
            case 0:
                newValueScaled = (newValue - 0.5f) * 360.0f;
                /* optim TBD: this changed-value check happens twice (in
                 * binauraliser_setSourceAzi_deg), same for the following checks...
                 * Setters could return a valueUpdated bool on successful update, e.g.
                 *   refreshWindow = binauraliser_setSourceAzi_deg(hBin, index/3, newValueScaled);
                 */ /*
                if (newValueScaled != binauraliser_getSourceAzi_deg(hBin, index/3)){
                    binauraliser_setSourceAzi_deg(hBin, index/3, newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 1:
                newValueScaled = (newValue - 0.5f) * 180.0f;
                if (newValueScaled != binauraliser_getSourceElev_deg(hBin, index/3)){
                    binauraliser_setSourceElev_deg(hBin, index/3, newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 2:
                newValueScaled = newValue * (ffThresh - nfThresh) + nfThresh;
                if (newValueScaled != binauraliserNF_getSourceDist_m(hBin, index/3)){
                    binauraliserNF_setSourceDist_m(hBin, index/3, newValueScaled);
                    //delayProcessors[i].setDistance(newValueScaled); which index to choose for "i"?
                    refreshWindow = true;
                }
                break;
            }
    }
}
*/

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

/*
float PluginProcessor::getParameter (int index)
{
    // standard parameters 
    if(index < k_NumOfParameters){
        switch (index) {
            case k_srcPosX:         return sourcePositionCurrent->x;
            case k_srcPosY:         return sourcePositionCurrent->y;
            case k_srcPosZ:         return sourcePositionCurrent->z;
            case k_lisPosX:         return listenerPositionCurrent->x;
            case k_lisPosY:         return listenerPositionCurrent->y;
            case k_lisPosZ:         return listenerPositionCurrent->z;
            case k_enableRotation:  return (float)binauraliser_getEnableRotation(hBin);
            case k_useRollPitchYaw: return (float)binauraliser_getRPYflag(hBin);
            case k_yaw:             return (binauraliser_getYaw(hBin)/360.0f) + 0.5f;
            case k_pitch:           return (binauraliser_getPitch(hBin)/180.0f) + 0.5f;
            case k_roll:            return (binauraliser_getRoll(hBin)/180.0f) + 0.5f;
            case k_flipYaw:         return (float)binauraliser_getFlipYaw(hBin);
            case k_flipPitch:       return (float)binauraliser_getFlipPitch(hBin);
            case k_flipRoll:        return (float)binauraliser_getFlipRoll(hBin);
            case k_numInputs:       return (float)(binauraliser_getNumSources(hBin))/(float)(MAX_NUM_INPUTS);
            default: return 0.0f;
        }
    }
    // source direction parameters 
    else{
        index-=k_NumOfParameters;
        switch (index % 3) {
            case 0:  return (binauraliser_getSourceAzi_deg(hBin, index/3) / 360.0f) + 0.5f;
            case 1:  return (binauraliser_getSourceElev_deg(hBin, index/3) / 180.0f) + 0.5f;
            case 2:  return (binauraliserNF_getSourceDist_m(hBin, index/3) - nfThresh) / (ffThresh - nfThresh);
            default: return 0.0f;
        }
    }
}
*/

/*
int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 3*MAX_NUM_INPUTS;
}
*/

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

/*
const String PluginProcessor::getParameterName (int index)
{
    // standard parameters 
    if(index < k_NumOfParameters){
        switch (index) {
            case k_srcPosX:         return "Source Position X";
            case k_srcPosY:         return "Source Position Y";
            case k_srcPosZ:         return "Source Position Z";
            case k_lisPosX:         return "Listener Position X";
            case k_lisPosY:         return "Listener Position Y";
            case k_lisPosZ:         return "Listener Position Z";
            case k_enableRotation:  return "enable_rotation";
            case k_useRollPitchYaw: return "use_rpy";
            case k_yaw:             return "yaw";
            case k_pitch:           return "pitch";
            case k_roll:            return "roll";
            case k_flipYaw:         return "flip_yaw";
            case k_flipPitch:       return "flip_pitch";
            case k_flipRoll:        return "flip_roll";
            case k_numInputs:       return "num_sources";
            default: return "NULL";
        }
    }
    // source direction parameters 
    else{
        index-=k_NumOfParameters;
        switch (index % 3) {
           case 0:  return TRANS("Azim_") + String(index/3);
           case 1:  return TRANS("Elev_") + String(index/3);
           case 2:  return TRANS("Dist_") + String(index/3);
           default: return "NULL";
        }
    }
}
*/

/*
const String PluginProcessor::getParameterText(int index)
{
    // standard parameters 
    if(index < k_NumOfParameters){
        switch (index) {
            case k_srcPosX:         return String(sourcePositionCurrent->x);
            case k_srcPosY:         return String(sourcePositionCurrent->y);
            case k_srcPosZ:         return String(sourcePositionCurrent->z);
            case k_lisPosX:         return String(listenerPositionCurrent->x);
            case k_lisPosY:         return String(listenerPositionCurrent->y);
            case k_lisPosZ:         return String(listenerPositionCurrent->z);
            case k_enableRotation:  return !binauraliser_getEnableRotation(hBin) ? "Off" : "On";
            case k_useRollPitchYaw: return !binauraliser_getRPYflag(hBin) ? "YPR" : "RPY";
            case k_yaw:             return String(binauraliser_getYaw(hBin));
            case k_pitch:           return String(binauraliser_getPitch(hBin));
            case k_roll:            return String(binauraliser_getRoll(hBin));
            case k_flipYaw:         return !binauraliser_getFlipYaw(hBin) ? "No-Flip" : "Flip";
            case k_flipPitch:       return !binauraliser_getFlipPitch(hBin) ? "No-Flip" : "Flip";
            case k_flipRoll:        return !binauraliser_getFlipRoll(hBin) ? "No-Flip" : "Flip";
            case k_numInputs:       return String(binauraliser_getNumSources(hBin));
            default: return "NULL";
        }
    }
    // source direction parameters 
    else{
        index-=k_NumOfParameters;
        switch (index % 3) {
            case 0:  return String(binauraliser_getSourceAzi_deg(hBin, index/3));
            case 1:  return String(binauraliser_getSourceElev_deg(hBin, index/3));
            case 2:  return String(binauraliserNF_getSourceDist_m(hBin, index/3));
            default: return "NULL";
        }
    }
}
*/

const String PluginProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PluginProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 0;
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

const String PluginProcessor::getProgramName (int /*index*/)
{
    return String(); 
}


bool PluginProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool PluginProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
}


bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

void PluginProcessor::changeProgramName (int /*index*/, const String& /*newName*/)
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
	nSampleRate = (int)(sampleRate + 0.5);

    delayLineSpec.maximumBlockSize = dfpSpec.maximumBlockSize = samplesPerBlock;
    delayLineSpec.sampleRate = dfpSpec.sampleRate = sampleRate;
    delayLineSpec.numChannels = 1; // formerly nNumInputs; DelayLines should work Mono
    dfpSpec.numChannels = 2; // DiffuseFieldProcessor works binaurally
    
	binauraliserNF_init(hBin, nSampleRate);
    AudioProcessor::setLatencySamples(binauraliser_getProcessingDelay());

    // initial setup for the Delay Processors
    initDelayProcessors(delayLineSpec);

    //Diffuse Field Processor initialization, but only when binRev was loaded from psx
    if(psxLoaded)       
        dfp.init(dfpSpec, mixingTime, sampleRate); // think of other things, that should only be done after psx import (?)
}

/* Call reset methods of all the dsp members */
void PluginProcessor::releaseResources()
{
    if (dfp.isInitialized())
    {
        dfp.convolver.reset();
        dfp.delayLineLP.reset();
    }

    for (auto it = delayProcessors.begin(); it != delayProcessors.end(); ++it)
    {
        auto& dp = *it;
        dp.resetDSP();
    }
}

//void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
void PluginProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    //nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    //nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());

    ////////////////////////////////////////////////////////////////////////////////////////////////
    binauraliserNF_data* bData = static_cast<binauraliserNF_data*>(hBin);
    AudioBuffer<float> dfpOutputBuffer(2, nCurrentBlockSize);

    if (!idleLoadingConfig) {
        // Resize buffer to NUM_DELAY_PROCESSORS (direct+reflections)
        buffer.setSize(NUM_DELAY_PROCESSORS, nCurrentBlockSize, true, false, false);
        
        // Fill the DiffuseFieldProcessor's internal buffer
        if (dfp.isInitialized()) {
            dfp.inputBuffer.setSize(2, nCurrentBlockSize, false, false, false);
            dfp.inputBuffer.copyFrom(0, 0, buffer, 0, 0, nCurrentBlockSize);
            dfp.inputBuffer.copyFrom(1, 0, buffer, 1, 0, nCurrentBlockSize);
        }

        // Fill the buffer for every DelayProcessor, unless it is muted by UI button click
        for (int inputChannelIndex = 2; inputChannelIndex < NUM_DELAY_PROCESSORS; ++inputChannelIndex) {
            if (!(delayProcessors[inputChannelIndex].getIsActive())) {
                // clear this channel of the buffer
                buffer.clear(inputChannelIndex, 0, nCurrentBlockSize);
            }
            else {
                // Copy input 0 to all inputs > 1
                buffer.copyFrom(inputChannelIndex, 0, buffer, 0, 0, nCurrentBlockSize);
            }
        }
        // first two channels cannot be cleared within the loop... 
        if(!delayProcessors[0].getIsActive())
            buffer.clear(0, 0, nCurrentBlockSize);
        if (!delayProcessors[1].getIsActive())
            buffer.clear(1, 0, nCurrentBlockSize);


        juce::dsp::AudioBlock<float> blockToProcess = juce::dsp::AudioBlock<float>(buffer);
        processContexts.clear(); // clear contexts array, then refill
    
        for (int processorIndex = 0; processorIndex < NUM_DELAY_PROCESSORS; ++processorIndex) {
            // Create one processing context for each channel and process each with one delay processor
            /*
            dsp::ProcessContextReplacing<float> tempContext(blockToProcess.getSubsetChannelBlock(processorIndex, 1));
            processContexts.insert(processorIndex, tempContext);
            delayProcessors[processorIndex].process(processContexts[processorIndex]);
            */
            
            processContexts.insert(processorIndex, dsp::ProcessContextReplacing<float>(blockToProcess.getSubsetChannelBlock(processorIndex, 1)));
            dsp::ProcessContextReplacing<float> tempContext(blockToProcess.getSubsetChannelBlock(processorIndex, 1));
            delayProcessors[processorIndex].process(tempContext);
            
            //specularGainProcessor.process(tempContext);
        }
    }

    nNumInputs = buffer.getNumChannels(); // Should be NUM_DELAY_PROCESSORS
    nNumOutputs = buffer.getNumChannels();

    // Binauraliser Code
    // float** bufferData = const_cast<float**>(buffer.getArrayOfWritePointers());
    float* pFrameData[MAX_NUM_CHANNELS]; // 64 at the moment, might turn that down to NUM_DELAY_PROCESSORS
    int frameSize = binauraliser_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < buffer.getNumChannels(); ch++) {
                //pFrameData[ch] = &bufferData[ch][frame*frameSize]; // originally
                pFrameData[ch] = buffer.getWritePointer(ch) + frame * frameSize;
            }

            /* perform specular processing */
            binauraliserNF_process(hBin, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
        }

        // Specular gain processing
        buffer.applyGain(0, 0, nCurrentBlockSize, specularGain);
        buffer.applyGain(1, 0, nCurrentBlockSize, specularGain);
        
        // Binaural Reverb processing
        if (dfpEnabled && !idleLoadingConfig) {
            dfp.process(dfpOutputBuffer);

            // buffer still has N=NUM_DELAY_PROCESSORS channels, but binaural mix is on channels 1&2 only
            // revAmplitude should already be applied to binRevWeighted via the inverse weighting function...
            // bnf processing somehow really lowers the amplitudes of the specular part, 
            // so bring in some attenuation here

            // then add dfpBuffer to the main output buffer
            buffer.addFrom(0, 0, dfpOutputBuffer, 0, 0, nCurrentBlockSize, diffuseGain);
            buffer.addFrom(1, 0, dfpOutputBuffer, 1, 0, nCurrentBlockSize, diffuseGain);
        }
    }
    else
        buffer.clear();
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

    // original code
    /*
    XmlElement xml("BINAURALISERNFPLUGINSETTINGS");
    for(int i=0; i<binauraliser_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), binauraliser_getSourceAzi_deg(hBin,i));
        xml.setAttribute("SourceElevDeg" + String(i), binauraliser_getSourceElev_deg(hBin,i));
        xml.setAttribute("SourceDistMeter" + String(i), binauraliserNF_getSourceDist_m(hBin,i));
    }
    xml.setAttribute("nSources", binauraliser_getNumSources(hBin));
    
    if(!binauraliser_getUseDefaultHRIRsflag(hBin))
        xml.setAttribute("SofaFilePath", String(binauraliser_getSofaFilePath(hBin)));
    
    xml.setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    xml.setAttribute("INTERP_MODE", binauraliser_getInterpMode(hBin));
    xml.setAttribute("ENABLE_ROT", binauraliser_getEnableRotation(hBin));
    xml.setAttribute("YAW", binauraliser_getYaw(hBin));
    xml.setAttribute("PITCH", binauraliser_getPitch(hBin));
    xml.setAttribute("ROLL", binauraliser_getRoll(hBin));
    xml.setAttribute("FLIP_YAW", binauraliser_getFlipYaw(hBin));
    xml.setAttribute("FLIP_PITCH", binauraliser_getFlipPitch(hBin));
    xml.setAttribute("FLIP_ROLL", binauraliser_getFlipRoll(hBin));
    xml.setAttribute("RPY_FLAG", binauraliser_getRPYflag(hBin));
    xml.setAttribute("HRIRdiffEQ", binauraliser_getEnableHRIRsDiffuseEQ(hBin));
    xml.setAttribute("OSC_PORT", osc_port_ID);
    
    copyXmlToBinary(xml, destData);
    */
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
    
    // original code
    /*
    
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr) {
        if (xmlState->hasTagName("BINAURALISERNFPLUGINSETTINGS")) {
            for(int i=0; i<binauraliser_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    binauraliser_setSourceAzi_deg(hBin, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    binauraliser_setSourceElev_deg(hBin, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceDistMeter" + String(i)))
                    binauraliserNF_setSourceDist_m(hBin, i, (float)xmlState->getDoubleAttribute("SourceDistMeter" + String(i), upperDistRange)); // default source distance is far field (no near field filtering)
                    // I should the DelayProcessor distance here.. but how?
            }
            if(xmlState->hasAttribute("nSources"))
               binauraliser_setNumSources(hBin, xmlState->getIntAttribute("nSources", 1)); 
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                binauraliser_setSofaFilePath(hBin, new_cstring);
            }
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            if(xmlState->hasAttribute("INTERP_MODE"))
                binauraliser_setInterpMode(hBin, xmlState->getIntAttribute("INTERP_MODE", 1));
            if(xmlState->hasAttribute("ENABLE_ROT"))
                binauraliser_setEnableRotation(hBin, xmlState->getIntAttribute("ENABLE_ROT", 0));
            if(xmlState->hasAttribute("YAW"))
                binauraliser_setYaw(hBin, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                binauraliser_setPitch(hBin, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                binauraliser_setRoll(hBin, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                binauraliser_setFlipYaw(hBin, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                binauraliser_setFlipPitch(hBin, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                binauraliser_setFlipRoll(hBin, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                binauraliser_setRPYflag(hBin, xmlState->getIntAttribute("RPY_FLAG", 0));
            if(xmlState->hasAttribute("HRIRdiffEQ"))
                binauraliser_setEnableHRIRsDiffuseEQ(hBin, xmlState->getIntAttribute("HRIRdiffEQ", 1));

            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            binauraliser_refreshSettings(hBin);
        }
    }
    */
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::saveConfigurationToFile (File destination)
{
    sources.removeAllChildren(nullptr);
    for (int i=0; i<binauraliser_getNumSources(hBin);i++)
    {
        sources.appendChild (ConfigurationHelper::
                             createElement(binauraliser_getSourceAzi_deg(hBin, i),
                                           binauraliser_getSourceElev_deg(hBin, i),
                                           binauraliserNF_getSourceDist_m(hBin, i),
                                           i+1, false, 1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA Binauraliser source directions and distances."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Binauraliser " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (sources, "Source Directions and Distances"));
    //jsonObj->setProperty ("LoudspeakerLayout", ConfigurationHelper::convertLoudspeakersToVar (sources, "Source Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    psxLoaded = false;
    idleLoadingConfig = true;
    int channelIDs[MAX_NUM_INPUTS+1] = {0};
    int virtual_channelIDs[MAX_NUM_INPUTS+1] = {0};
    sources.removeAllChildren(nullptr);
    //
    //Result result = ConfigurationHelper::parseFileForGenericLayout (configFile, sources, nullptr);
    Result result = ParaspaxConfigurationHelper::parseFileForParaspaxVariables(configFile, sources, nullptr, 
                                                                               rirBuffer, dfp.binRevBuffer, 
                                                                               dfp.inverseWeightingFunc, startEndArray,
                                                                               mixingTime, brirSpecGain,
                                                                               *listenerPositionInit, *listenerPositionCurrent, *sourcePositionInit, *roomDims);
    //Result result = ConfigurationHelper::parseFileForLoudspeakerLayout (configFile, sources, nullptr);
    if(result.wasOk()){
        int num_srcs, num_virtual_srcs, src_idx, jj;
        num_srcs = num_virtual_srcs = src_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = sources.begin(); it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_srcs++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_srcs] = (*it).getProperty("Channel");
                num_virtual_srcs++; channelIDs[jj] = -1;
            }
            jj++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_srcs+num_virtual_srcs; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        // apply some boost to the Gain Slider (minimal gain value passed on in psx struct)
        // map the linear gain value to the gainParam range (-60 to 6 on GUI, 0 to 1 internally)
        auto* specGainParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("specGain"));
        float specGainInDb = juce::Decibels::gainToDecibels(brirSpecGain);
        specGainInDb = juce::jlimit(-60.0f, 6.0f, specGainInDb);
        float normalizedValue = juce::jmap(specGainInDb, -60.0f, 6.0f, 0.0f, 1.0f);
        if (specGainParam != nullptr)
            specGainParam->setValueNotifyingHost(normalizedValue);
        
        /* update with the new configuration  */
        /* WARNING: the execution of the following block for some reason overwrites the values of mixingTime & revAmplitude */
        binauraliser_setNumSources(hBin, num_srcs);
        for (ValueTree::Iterator it = sources.begin() ; it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                binauraliser_setSourceAzi_deg(hBin, channelIDs[src_idx]-1, (*it).getProperty("Azimuth"));
                binauraliser_setSourceElev_deg(hBin, channelIDs[src_idx]-1, (*it).getProperty("Elevation"));
                binauraliserNF_setSourceDist_m(hBin, channelIDs[src_idx]-1, (*it).getProperty("Radius"));          
                src_idx++;
            }
        }
        
        // this will be checked by PluginEditor's timer callback
        updateRoomDims = true;
        updateXyPadPosition = true; 
        
        refreshWindow = true; // binauraliserNF stuff
        psxLoaded = true; // now the DelayProcessors can get their MIR excerpts

        // change apvts source/listener-position parameter/slider ranges here
        updatePositionParameterRanges();
        
        initDelayProcessors(delayLineSpec);
        dfp.init(dfpSpec, mixingTime, delayLineSpec.sampleRate);

        
        idleLoadingConfig = false; // this flag is to prevent most of the processing in the processBlock() method during config load
    }
}

void PluginProcessor::extrapolate()
{   
    // always look at the listener translation related to the original position
    Vector3D<float> translation(*listenerPositionCurrent - *listenerPositionInit);
    // get the source coordinate translation
    Vector3D<float> srcTranslation(*sourcePositionCurrent - *sourcePositionInit);
    // combine both translations
    Vector3D<float> totalTranslation(translation - srcTranslation);

    // Get all azis & eles; transform into radians and then cartesian
    // also take all distances
    for (auto it = delayProcessors.begin(); it != delayProcessors.end(); ++it)
    {
        auto& dp = *it;
        float x = dp.initCoords.x;
        float y = dp.initCoords.y;
        float z = dp.initCoords.z;
        float aziExtrap, eleExtrap, disExtrap;

        // Get index of current DelayProcessor instance
        int dpIndex = std::distance(delayProcessors.begin(), it);
        
        // initial cartesian coordinates already calculated in initDelayProcessors()
        // translate x, y & z by the translation vector above
        x -= totalTranslation.x;
        y -= totalTranslation.y;
        z -= totalTranslation.z;

        // Convert shifted Cartesian coordinates back to spherical coordinates
        CoordHelpers::cartesian2sphericalBnf(x, y, z, aziExtrap, eleExtrap, disExtrap);

        // caused audio to stutter (probably blocked the audio processing) 
        // when moving the positioner thumb too much
        //std::lock_guard<std::mutex> lock(extrapolMutex);

        // Update DelayProcessors with new spherical values
        // includes adaption of delay time (toa) and amplitude
        dp.setAzimuth(aziExtrap);
        dp.setElevation(eleExtrap);
        dp.setDistance(disExtrap);

        // Update Diffuse Field Processor delay to match with onset of direct sound
        // To-Do: Check if this makes sense
        if (dpIndex == 0)
            dfp.setDelayByDistance(disExtrap - dp.initCoords.distance);

        // Update BNF spherical coordinates
        binauraliser_setSourceAzi_deg(hBin, dpIndex, aziExtrap);
        binauraliser_setSourceElev_deg(hBin, dpIndex, eleExtrap);
        binauraliserNF_setSourceDist_m(hBin, dpIndex, disExtrap);

        // fetch DelayProcessor's gainFactor in PluginProcessor 
        // and pass on to binauraliser_setSourceGain()
        binauraliser_setSourceGain(hBin, dpIndex, dp.getGainFactor());
    }
    // tell Editor to call pannerView::refreshPanView()
    setRefreshWindow(true);

    return;
}

void PluginProcessor::initDelayProcessors(juce::dsp::ProcessSpec& spec)
{
    double sampleRate = spec.sampleRate;
    binauraliserNF_data* bData = static_cast<binauraliserNF_data*>(hBin);

    delayProcessors.clear();

    for (int i = 0; i < NUM_DELAY_PROCESSORS; ++i) {
        delayProcessors.push_back(std::move(DelayProcessor(MAX_DELAY, sampleRate)));
        
        float a, b, c = 0.f;
        
        // experiment with rampLengths for SmoothedValue
        delayProcessors[i].currentDelaySmoothed.reset(spec.sampleRate, 0.01);

        // initialize spherical coordinates for the sound/image source that this dp represents
        delayProcessors[i].setInitialDistance(bData->src_dists_m[i]);
        delayProcessors[i].setInitialAzimuth(bData->src_dirs_deg[i][0]);
        delayProcessors[i].setInitialElevation(bData->src_dirs_deg[i][1]);
        // pre-compute the cartesian coords for later use in extrapolate function
        CoordHelpers::sphericalBnf2cartesian(bData->src_dirs_deg[i][0], bData->src_dirs_deg[i][1], bData->src_dists_m[i],
                                             delayProcessors[i].initCoords.x, delayProcessors[i].initCoords.y, delayProcessors[i].initCoords.z);

        //test, delete me!!!
        CoordHelpers::cartesian2sphericalBnf(delayProcessors[i].initCoords.x, delayProcessors[i].initCoords.y, delayProcessors[i].initCoords.z, a, b, c);
        
        // if json config has been loaded, extract the mir part that is used for filtering
        if (psxLoaded) {
            delayProcessors[i].setRirExcerpt(rirBuffer, startEndArray[0][i], startEndArray[1][i], spec);
        }

        // prepare convolution unit and delay line
        delayProcessors[i].prepare(spec);
    }

    bData->nSources = bData->new_nSources = delayProcessors.size();
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    // if a position parameter has been altered, update the delay processors
    if (parameterID == "srcPosX")
    {
        sourcePositionCurrent->x = newValue; updateDelayProcessorParams = true;
    }
    else if (parameterID == "srcPosY")
    {
        sourcePositionCurrent->y = newValue; updateDelayProcessorParams = true;
    }
    else if (parameterID == "srcPosZ")
    {
        sourcePositionCurrent->z = newValue; updateDelayProcessorParams = true;
    }
    else if (parameterID == "lisPosX")
    {
        listenerPositionCurrent->x = newValue; updateDelayProcessorParams = true;
    }
    else if (parameterID == "lisPosY")
    {
        listenerPositionCurrent->y = newValue; updateDelayProcessorParams = true;
    }
    else if (parameterID == "lisPosZ")
    {
        listenerPositionCurrent->z = newValue; updateDelayProcessorParams = true;
    }
    
    // Gain handlers
    else if (parameterID == "specGain")
    {
        specularGain = Decibels::decibelsToGain(newValue);
    }
    else if (parameterID == "diffGain")
    {
        diffuseGain = Decibels::decibelsToGain(newValue);
    }
}

/**
* After the psx data has been loaded it is required to re-define the ranges for the position slider
* They have to be instantiated somehow when the PluPro constructor gets called and here we give them their real values
*/
void PluginProcessor::updatePositionParameterRanges()
{
    auto* srcPosXParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("srcPosX"));
    if (srcPosXParam != nullptr)
        srcPosXParam->range = NormalisableRange<float>(0.f, roomDims->x);

    auto* srcPosYParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("srcPosY"));
    if (srcPosYParam != nullptr)
        srcPosYParam->range = NormalisableRange<float>(0.f, roomDims->y);

    auto* srcPosZParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("srcPosZ"));
    if (srcPosZParam != nullptr)
        srcPosZParam->range = NormalisableRange<float>(0.f, roomDims->z);

    auto* lisPosXParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosX"));
    if (lisPosXParam != nullptr)
        lisPosXParam->range = NormalisableRange<float>(0.f, roomDims->x);

    auto* lisPosYParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosY"));
    if (lisPosYParam != nullptr)
        lisPosYParam->range = NormalisableRange<float>(0.f, roomDims->y);

    auto* lisPosZParam = dynamic_cast<AudioParameterFloat*>(apvts.getParameter("lisPosZ"));
    if (lisPosZParam != nullptr)
        lisPosZParam->range = NormalisableRange<float>(0.f, roomDims->z);
}


