#include "AxialTurbine.h"
#include "imgui.h"

void TurboVis::AxialTurbine::CalculateVelocityTriangles()
{
    float tana1 = (workCoefficient - 2 * degreeOfReaction + 2) / (2 * flowCoefficient);
    float tanb2 = -(workCoefficient + 2 * degreeOfReaction) / (2 * flowCoefficient);
    float tanb1 = tana1 - 1 / flowCoefficient;
    float tana2 = tanb2 + 1 / flowCoefficient;

    float axialSpeed = flowCoefficient * rotationalSpeed;
    // float axialSpeed2 = rotationalSpeed / (tana2 - tanb2); // Should give the same result

    U = Vec(0, rotationalSpeed);

    // Incoming flow vectors
    W1 = Vec(axialSpeed, tanb1 * axialSpeed);
    V1 = Vec(axialSpeed, tana1 * axialSpeed);

    // Outgoing flow vectors
    W2 = Vec(axialSpeed, tanb2 * axialSpeed);
    V2 = Vec(axialSpeed, tana2 * axialSpeed);
}

void TurboVis::AxialTurbine::ShowFlowAngleSettings(bool bRepeatedStage)
{
    // In a turbine, only the inflow angle can be set, since it begins with a stator.

    if (!bRepeatedStage)
    {
        ImGui::DragFloat("Inflow angle", &stageInflowAngle, 0.1f, -90.f, 90.0f, "a0 = %.1f", ImGuiSliderFlags_AlwaysClamp);
    }
}
