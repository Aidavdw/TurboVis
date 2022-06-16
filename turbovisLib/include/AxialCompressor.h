// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#pragma once
#include "Stage.h"

namespace TurboVis
{
    class AxialCompressor : public Stage
    {
    public:
        AxialCompressor() :
            Stage(0.8, 0.6, 0.5, 1)
        {
            flowCoefficientRange = "Flow Coefficient [0.4 - 1.1]";
            workCoefficientRange = "Work Coefficient [0.3 - 0.6]";
            degreeOfReactionRange = "Degree of Reaction (0 is impulse stage)";
        };

        AxialCompressor(const float flowCoefficient, const float workCoefficent, const float degreeOfReaction, const float rotationalSpeed) :
            Stage(flowCoefficient, workCoefficent, degreeOfReaction, rotationalSpeed)
        {
            flowCoefficientRange = "Flow Coefficient [0.4 - 1.1]";
            workCoefficientRange = "Work Coefficient [0.3 - 0.6]";
            degreeOfReactionRange = "Degree of Reaction (0 is impulse stage)";
        };

        ~AxialCompressor()
        {
            
        };

        


        /* Virtual functions, strategy pattern*/
    public:
        virtual void ProcessDutyCoefficients();
    protected:
        // Shows the a0 & a3 flow angles. Different for types of stages, so defined in subclass.
        virtual void ShowFlowAngleSettings(bool bRepeatedStage);

        virtual void DrawAirfoilPlot(const int labelVerbosity, const bool bAllowAirfoilEdit, const int triangleDisplayLevel, const float rotorPitch, const float statorPitch, const bool bDisplayAngles, const bool bAnimate);
    };

}
