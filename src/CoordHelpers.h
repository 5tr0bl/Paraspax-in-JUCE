/*
  ==============================================================================

    CoordHelpers.h
    Created: 16 Apr 2024 6:30:03pm
    Author:  Micha

  ==============================================================================
*/

#pragma once
#include <cmath>

/**
*   Is taking floats as input type enough here?
*/
class CoordHelpers {
public:
    /* This receives sph. Coords in Bnf Format. */
    static void sphericalBnf2cartesian(float az, float elev, float r, float& x, float& y, float& z) {
        float normalizedAzimuth = fmod(az + 360.0f, 360.0f);
        float azimuthRad = juce::MathConstants<float>::pi * normalizedAzimuth / 180.0f;
        float elevationRad = juce::MathConstants<float>::pi * elev / 180.0f;

        //x = r * std::sin(azimuthRad);
        x = r * std::sin(azimuthRad) * std::cos(elevationRad);
        x *= -1.f;
        y = r * std::cos(azimuthRad) * std::cos(elevationRad);
        z = r * std::sin(elevationRad);
      
        // original
        //double rcoselev = r * std::cos(elev);
        //x = rcoselev * std::cos(azi_mapped);
        //y = rcoselev * std::sin(azi_mapped);
    }

    /* This returns sph. Coords in Bnf Format */
    static void cartesian2sphericalBnf(float x, float y, float z, float& az, float& elev, float& r) {
        //double hypotxy = std::hypot(x, y);
        //r = std::hypot(hypotxy, z);
        float hypotxy = std::sqrt(x * x + y * y);
        r = std::sqrt(x * x + y * y + z * z);

        elev = std::atan2(z, hypotxy);
        elev = radiansToDegrees(elev);

        float tmpY = -1.f * x;
        float tmpX = y;
        az = std::atan2(tmpY, tmpX);
        az = radiansToDegrees(az);
        az = aziSph2aziBnf(az);
    }

    static float aziBnf2aziSph(float newAzi) {
        // BNF azi [0(front), 90(left), 180/-180(back), -90(right)]
        // Target azi [0(front), 90(left), 180(back), 270(right)]
        if (newAzi < 0) {
            return newAzi + 360.0f;
        }
        else {
            return newAzi;
        }
    }

    static float aziSph2aziBnf(float newAzi) {
        // BNF azi [0(front), 90(left), 180/-180(back), -90(right)]
        // Psx azi [0(front), 90(left), 180(back), 270(right)]
        if (newAzi > 180) {
            return newAzi - 360.0f;
        }
        else {
            return newAzi;
        }
    }
};