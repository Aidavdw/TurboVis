// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#pragma once
#include "Stage.h"

namespace TurboVis
{
    class AxialTurbine : public Stage
    {
    public:
        AxialTurbine() :
            Stage(2, 1, 0.5, 1)
        {};

        AxialTurbine(const float flowCoefficient, const float workCoefficent, const float degreeOfReaction, const float rotationalSpeed) :
            Stage(flowCoefficient, workCoefficent, degreeOfReaction, rotationalSpeed)
        {};

        ~AxialTurbine()
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
