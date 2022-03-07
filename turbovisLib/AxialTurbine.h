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

        void CalculateVelocityTriangles() override;

        void ShowFlowAngleSettings(bool bRepeatedStage) override;
    };

}
