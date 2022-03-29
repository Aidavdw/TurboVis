// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#pragma once
#include <string>
#include <math.h>

struct ImVec4;

namespace TurboVis
{
    #define PI 3.14159265

    /* A vector in the tangential-axial plane. Abbreviated as Vec to not be confused with std::vec*/
    struct Vec
    {
        Vec() :
            axialComponent(0),
            tangentialComponent(0)
        {};

        Vec(const float axialComponent, const float tangentialComponent) :
            axialComponent(axialComponent),
            tangentialComponent(tangentialComponent)
        {};

        // Given only an angle, construct a unit vector in that direction
        Vec(const float angle)
        {
            axialComponent = cos(angle*PI/180);
            tangentialComponent = sin(angle*PI/180);
        };

        float axialComponent;
        float tangentialComponent;

        float Magnitude() const;

        /* Calculates the angle between the axial axis. Counterclockwise positive. */
        float Angle() const;

        // returns normalised version of vec.
        Vec GetNormalised() const;

        void PlotLine(const Vec& origin, const std::string& label, const ImVec4 colour, int labelVerbosity, bool bFlipLabel, bool bDisplayAngle, const bool bDisplayArrows) const;

        Vec operator+ (const Vec& other) const
        {
            Vec res = other;
            res.axialComponent += axialComponent;
            res.tangentialComponent += tangentialComponent;
            return res;
        }

        Vec operator- (const Vec& other) const
        {
            Vec res = other;
            res.axialComponent -= axialComponent;
            res.tangentialComponent -= tangentialComponent;
            return res;
        }

        Vec operator* (const float scale) const
        {
            Vec res = *this;
            res.axialComponent *= scale;
            res.tangentialComponent *= scale;
            return res;
        }
        
    };

}
