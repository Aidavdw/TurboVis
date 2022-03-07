#pragma once
#include "Stage.h"

namespace TurboVis
{
    class AxialCompressor : public Stage
    {
    public:
        AxialCompressor() :
            Stage(2, 1, 0.5, 1)
        {};

        AxialCompressor(const float flowCoefficient, const float workCoefficent, const float degreeOfReaction, const float rotationalSpeed) :
            Stage(flowCoefficient, workCoefficent, degreeOfReaction, rotationalSpeed)
        {};

        void CalculateVelocityTriangles() override;

        void ShowFlowAngleSettings(bool bRepeatedStage) override;

        void DrawAirfoilPlot(const int labelVerbosity, const bool bAllowAirfoilEdit, const int triangleDisplayLevel, const float rotorPitch, const float statorPitch, const bool bDisplayAngles, const bool bAnimate) override;
    };

}
