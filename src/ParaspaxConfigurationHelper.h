/*
 ==============================================================================
 This file is based on the file "ConfigurationHelper.h" of the IEM plug-in suite.
 Original Author: Daniel Rudrich
 Copyright (c) 2017 - Institute of Electronic Music and Acoustics (IEM)
 https://iem.at
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class ParaspaxConfigurationHelper {
public:
    // =============== IMPORT ======================================================
        /**
         Loads a JSON-file (fileToParse) and writes the parsed content to a var object (dest).
         */
    static Result parseFile(const File& fileToParse, var& dest)
    {
        if (!fileToParse.exists())
            return Result::fail("File '" + fileToParse.getFullPathName() + "' does not exist!");

        String jsonString = fileToParse.loadFileAsString();
        Result result = JSON::parse(jsonString, dest);
        if (!result.wasOk())
            return Result::fail("File '" + fileToParse.getFullPathName() + "' could not be parsed:\n" + result.getErrorMessage());

        return Result::ok();
    }

    /**
         Custom Parser for Paraspax Variables contained in psx struct
        */
    static Result parseFileForParaspaxVariables(const File& fileToParse, ValueTree& elements, UndoManager* undoManager,
                                                juce::AudioBuffer<float>& rirBuffer, juce::AudioBuffer<float>& binRevBuffer,
                                                juce::AudioBuffer<float>& wfInvBuffer, std::vector<std::vector<int>>& startEndArray,
                                                float& mixingTime, float& revAmplitude,
                                                Vector3D<float>& listenerPositionInit, Vector3D<float>& listenerPositionCurrent, Vector3D<float>& sourcePositionInit, Vector3D<float>& roomDimensions)
    {
        // parse configuration file
        var parsedJson;
        Result result = parseFile(fileToParse, parsedJson);
        if (!result.wasOk())
            return Result::fail(result.getErrorMessage());

        // first some basics
        int fs = 48000; 
        float c = 343.f;
        if (parsedJson.hasProperty("fs"))
            fs = parsedJson.getProperty("fs", int());
        if (parsedJson.hasProperty("c"))
            c = parsedJson.getProperty("c", float());

        // looks for a 'GenericLayout' or 'LoudspeakerLayout' object
        var genericLayout;
        if (parsedJson.hasProperty("GenericLayout"))
            genericLayout = parsedJson.getProperty("GenericLayout", var());
        else if (parsedJson.hasProperty("LoudspeakerLayout"))
            genericLayout = parsedJson.getProperty("LoudspeakerLayout", var());
        else
            return Result::fail("No 'GenericLayout' or 'LoudspeakerLayout' object found in the configuration file.");

        // looks for a 'GenericLayout' or 'LoudspeakerLayout' object
        var elementArray;
        if (genericLayout.hasProperty("Elements"))
            elementArray = genericLayout.getProperty("Elements", var());
        else if (genericLayout.hasProperty("Loudspeakers"))
            elementArray = genericLayout.getProperty("Loudspeakers", var());
        else
            return Result::fail("No 'Elements' or 'Loudspeakers' attribute found within the 'GenericLayout' or 'LoudspeakerLayout' object.");

        result = addElementsToValueTree(elementArray, elements, undoManager);

        if (!result.wasOk())
            return Result::fail(result.getErrorMessage());

        // look for rir float array in JSON and map to PluginProcessor rir float array
        var psxRir;
        if (parsedJson.hasProperty("rir"))
            psxRir = parsedJson.getProperty("rir", var());
        else
            return Result::fail("No 'rir' object found in the configuration file.");

        if (psxRir.isArray())
        {
            auto rirArrayVar = psxRir.getArray();
            int numChannels = 1; // Assuming mono channel
            int numSamples = rirArrayVar->size();

            rirBuffer.setSize(numChannels, numSamples);
            for (int i = 0; i < numSamples; ++i) {
                float sample = static_cast<float>(rirArrayVar->getUnchecked(i));
                rirBuffer.setSample(0, i, sample);
            }
        }
        else
            return Result::fail("Invalid data type for rir");

        // look for lists with start and end indices of the mir for the respective DelayProcessors
        var startIndVar, endIndVar;
        if (parsedJson.hasProperty("rirStartIndices") && parsedJson.hasProperty("rirEndIndices")) {
            startIndVar = parsedJson.getProperty("rirStartIndices", var());
            endIndVar = parsedJson.getProperty("rirEndIndices", var());
        }
        else {
            return Result::fail("No lists of start/end indices found in the configuration file.");
        }

        if (startIndVar.isArray() && endIndVar.isArray())
        {
            auto arrayS = startIndVar.getArray();
            auto arrayE = endIndVar.getArray();
            int numIndices = arrayS->size();

            for (int idx = 0; idx < numIndices; ++idx) {
                startEndArray[0][idx] = arrayS->getUnchecked(idx);
                startEndArray[1][idx] = arrayE->getUnchecked(idx);
            }
        }
        else
            return Result::fail("Invalid data type for lists of indices");

        // look for binRev float array in JSON and map to PluginProcessor->DiffuseFieldProcessor binRev float array
        var psxBinRevL, psxBinRevR;
        if (parsedJson.hasProperty("binRevL") && parsedJson.hasProperty("binRevR"))
        {
            psxBinRevL = parsedJson.getProperty("binRevL", var());
            psxBinRevR = parsedJson.getProperty("binRevR", var());
        }
        else
            return Result::fail("No 'binRev' object found in the configuration file.");

        if (psxBinRevL.isArray() && psxBinRevR.isArray())
        {
            auto arrayLeft = psxBinRevL.getArray();
            auto arrayRight = psxBinRevR.getArray();

            int numChannels = 2;
            int numSamples = arrayLeft->size();

            binRevBuffer.setSize(numChannels, numSamples);

            for (int i = 0; i < numSamples; ++i) {
                binRevBuffer.setSample(0, i, static_cast<float>(arrayLeft->getUnchecked(i)));
                binRevBuffer.setSample(1, i, static_cast<float>(arrayRight->getUnchecked(i)));
            }

        }
        else
            return Result::fail("Invalid data type for binRev");

        // look for inverse weighting function in psx struct. Write to DFP
        // maybe using an AudioBuffer for wfInv is not the best option
        var psxWfInv;
        if (parsedJson.hasProperty("wfInv"))
            psxWfInv = parsedJson.getProperty("wfInv", var());
        else
            return Result::fail("No 'wfInv' object found in the configuration file.");

        if (psxWfInv.isArray())
        {
            auto wfInvVar = psxWfInv.getArray();
            int numChannels = 1;
            int numSamples = wfInvVar->size();

            wfInvBuffer.setSize(numChannels, numSamples);
            for (int i = 0; i < numSamples; ++i) {
                wfInvBuffer.setSample(0, i, static_cast<float>(wfInvVar->getUnchecked(i)));
            }
        }

        // look for reverb amplitude as set in synthesizeBRIR.m l.107
        var revAmpVar;
        if (parsedJson.hasProperty("revAmplitude")) {
            revAmpVar = parsedJson.getProperty("revAmplitude", var());
            revAmplitude = revAmpVar;
        }
        else
            return Result::fail("No 'revAmplitude' object found in the configuration file.");

        // look for mixingTime in psx struct; mtAbel is the one used, later multiplied by 2
        var mtVar;
        if (parsedJson.hasProperty("mixingTime")) {
            mtVar = parsedJson.getProperty("mixingTime", var());
            mixingTime = mtVar;
        }
        else
            return Result::fail("No 'mixingTime' object found in the configuration file.");

        // look for room dimensions
        var roomDimsLengthVar, roomDimsWidthVar, roomDimsHeightVar;
        if (parsedJson.hasProperty("roomHeight") && parsedJson.hasProperty("roomLength") && parsedJson.hasProperty("roomWidth")) {
            roomDimsLengthVar = parsedJson.getProperty("roomLength", var());
            roomDimsWidthVar = parsedJson.getProperty("roomWidth", var());
            roomDimsHeightVar = parsedJson.getProperty("roomHeight", var());
            roomDimensions.x = roomDimsWidthVar; // short side of the room
            roomDimensions.y = roomDimsLengthVar; // long side of the room
            roomDimensions.z = roomDimsHeightVar;
        }
        else
            return Result::fail("No room dimensions found in the configuration file.");

        // look for listener & source positions
        var lisPosVar, srcPosVar;
        if (parsedJson.hasProperty("srcPos") && parsedJson.hasProperty("lisPos")) {
            lisPosVar = parsedJson.getProperty("lisPos", var());
            srcPosVar = parsedJson.getProperty("srcPos", var());
        }
        else
            return Result::fail("No source and/or listener positions found in the configuration file.");

        if (lisPosVar.isArray() && srcPosVar.isArray()) {
            auto lisArray = lisPosVar.getArray();
            auto srcArray = srcPosVar.getArray();
            float psxSrcX = srcArray->getUnchecked(0);
            float psxSrcY = srcArray->getUnchecked(1);
            float psxLisX = lisArray->getUnchecked(0);
            float psxLisY = lisArray->getUnchecked(1);

            // x coord is the inverted original y coord [x = roomWidth-y]
            listenerPositionInit.x = listenerPositionCurrent.x = roomDimensions.x - psxLisY;
            sourcePositionInit.x = roomDimensions.x - psxSrcY;

            // y coord is the original x coord
            // remeber to apply a vertical flip mapping in xy pad
            listenerPositionInit.y = listenerPositionCurrent.y = psxLisX;
            sourcePositionInit.y = psxSrcX;

            // z coords stay the same
            listenerPositionInit.z = listenerPositionCurrent.z = lisArray->getUnchecked(2);
            sourcePositionInit.z = srcArray->getUnchecked(2);
        }
        else
            return Result::fail("Error on retrieving source/listener positions from configuration file.");
        
        return Result::ok();
    }

    /**
    * Converts times of arrival (toa) to distance as used by binauraliser nf
    * Obsolete, as this handling now already happens in jsonDump.m on Matlab side
    */
    static float convertToaToDistance(float toa, const int fs, const float c)
    {
        // toa from psx struct comes in [samples]
        float toaInSeconds = toa / fs;
        return toaInSeconds * c;
    }

    /**
     Appends all elements within the GenericLayout to the elements ValueTree.
     */

    static Result addElementsToValueTree(var& elementArray, ValueTree& elements, UndoManager* undoManager)
    {
        if (!elementArray.isArray())
            return Result::fail("'elementArray' is not an array.");

        const int nElements = elementArray.size();

        for (int i = 0; i < nElements; ++i)
        {
            var& element = elementArray[i];
            float azimuth, elevation, radius, gain;
            int channel;
            bool isImaginary;

            if (!element.hasProperty("Azimuth"))
                return Result::fail("No 'Azimuth' attribute for element #" + String(i + 1) + ".");
            var azi = element.getProperty("Azimuth", var());
            if (azi.isDouble() || azi.isInt())
                azimuth = azi;
            else
                return Result::fail("Wrong datatype for attribute 'Azimuth' for element #" + String(i + 1) + ".");

            if (!element.hasProperty("Elevation"))
                return Result::fail("No 'Elevation' attribute for element #" + String(i + 1) + ".");
            var ele = element.getProperty("Elevation", var());
            if (ele.isDouble() || ele.isInt())
                elevation = ele;
            else
                return Result::fail("Wrong datatype for attribute 'Elevation' for element #" + String(i + 1) + ".");

            if (!element.hasProperty("Radius"))
                return Result::fail("No 'Radius' attribute for element #" + String(i + 1) + ".");
            var rad = element.getProperty("Radius", var());
            if (rad.isDouble() || rad.isInt())
                radius = rad;
            else
                return Result::fail("Wrong datatype for attribute 'Radius' for element #" + String(i + 1) + ".");

            if (!element.hasProperty("Gain"))
                return Result::fail("No 'Gain' attribute for element #" + String(i + 1) + ".");
            var g = element.getProperty("Gain", var());
            if (g.isDouble() || g.isInt())
                gain = g;
            else
                return Result::fail("Wrong datatype for attribute 'Gain' for element #" + String(i + 1) + ".");

            if (!element.hasProperty("Channel"))
                return Result::fail("No 'Channel' attribute for element #" + String(i + 1) + ".");
            var ch = element.getProperty("Channel", var());
            if (ch.isInt())
                channel = ch;
            else
                return Result::fail("Wrong datatype for attribute 'Channel' for element #" + String(i + 1) + ".");

            if (!element.hasProperty("IsImaginary"))
                return Result::fail("No 'IsImaginary' attribute for element #" + String(i + 1) + ".");
            var im = element.getProperty("IsImaginary", var());
            if (im.isBool())
                isImaginary = im;
            else
                return Result::fail("Wrong datatype for attribute 'IsImaginary' for element #" + String(i + 1) + ".");

            elements.appendChild(createElement(azimuth, elevation, radius, channel, isImaginary, gain), undoManager);
        }

        return Result::ok();
    }

    /**
         Creates a single element ValueTree, which can be appended to another ValueTree holding several elements.
         */
    static ValueTree createElement(const float azimuth, const float elevation, const float radius, const int channel, const bool isImaginary, const float gain)
    {
        ValueTree newElement("Element");

        newElement.setProperty("Azimuth", azimuth, nullptr);
        newElement.setProperty("Elevation", elevation, nullptr);
        newElement.setProperty("Radius", radius, nullptr);
        newElement.setProperty("Channel", channel, nullptr);
        newElement.setProperty("Imaginary", isImaginary, nullptr);
        newElement.setProperty("Gain", gain, nullptr);

        return newElement;
    }
};
