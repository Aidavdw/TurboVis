#include "AxialCompressor.h"
#include "imgui.h"

void TurboVis::AxialCompressor::CalculateVelocityTriangles()
{
    float tana1 = - (workCoefficient + 2 * degreeOfReaction - 2) / (2 * flowCoefficient);
    float tanb2 = (workCoefficient - 2 * degreeOfReaction) / (2 * flowCoefficient);
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

void TurboVis::AxialCompressor::ShowFlowAngleSettings(bool bRepeatedStage)
{
    // In a compressor, only the outflow angle can be set, as the stator comes last.

    if (!bRepeatedStage)
    {
        ImGui::DragFloat("Outflow angle", &stageOutflowAngle, 0.1f, -90.f, 90.0f, "a3 = %.1f", ImGuiSliderFlags_AlwaysClamp);
    }
    else
    {
        // a1 = a3. Since inflow V is known, this means that stator outflow V must be the same!
        stageOutflowAngle = V1.Angle();
    }
}

void TurboVis::AxialCompressor::DrawAirfoilPlot(const int labelVerbosity, const bool bAllowAirfoilEdit, const int triangleDisplayLevel, const float rotorPitch, const float statorPitch, const bool bDisplayAngles, const bool bAnimate)
{
    //float airfoilOffset = 1.2f;
    float offsetFromLE = 0.1f;
    // In a compressor, the rotor comes first, and then the stator.

    // Animation logic
    static float animationFrac = 0.f;
    static float animationScale = 0.02f;

    if (bAnimate)
    {
        // Make the speed of the animation dependent on U. Amplify the effect when it's near 1, make it less when it's higher.
        animationFrac += log(U.tangentialComponent + 0.5) * animationScale;
        if (animationFrac > 1.f)
            animationFrac--;
    }
    else
        animationFrac = 0.;

    // rotor
    static ImPlotPoint rotorTrailingEdgePoint = ImPlotPoint(-0.2f, 1.f);
    static ImPlotPoint rotorCurvatureControl = ImPlotPoint(-0.25f, 0.5f);
    Vec rotorLeadingEdge;
    Vec rotorTrailingEdge = AddAirfoilToPlot("Rotor", rotorLeadingEdge, W1, W2, rotorTrailingEdgePoint, rotorCurvatureControl, labelVerbosity, bAllowAirfoilEdit, rotorPitch, animationFrac, 0);

    // All the velocity triangles here are scaled relative to the length of W1!
    float scale = 1 / W1.Magnitude();

    // stator
    static ImPlotPoint statorTrailingEdgePoint = ImPlotPoint(0.7f, 3.4f);
    static ImPlotPoint statorCurvatureControl = ImPlotPoint(-0.5f, 3.f);
    Vec outflowVec = Vec(stageOutflowAngle);
    Vec statorLeadingEdge = V2*scale*(1+2*offsetFromLE) + rotorTrailingEdge;
    Vec statorTrailingEdge = AddAirfoilToPlot("Stator", statorLeadingEdge, V2, outflowVec, statorTrailingEdgePoint, statorCurvatureControl, labelVerbosity, bAllowAirfoilEdit, statorPitch, 0, 2);

    // velocity triangle in front of rotor
    if (triangleDisplayLevel > 0)
    {
        // as starting point, use -w1 so that w1 ends up directly in the airfoil. also normalise triangle.

        
        Vec frontTriangleOrigin = rotorLeadingEdge + (W1 * (scale *(1 +offsetFromLE)) * -1);
        
        
        (W1*scale).PlotLine(frontTriangleOrigin, "W1", WColour, labelVerbosity, true, bDisplayAngles, false);
        if (triangleDisplayLevel > 2)
        {
            (V1*scale).PlotLine(frontTriangleOrigin, "V1", VColour, labelVerbosity, true, bDisplayAngles, false);
            (U*scale).PlotLine(frontTriangleOrigin + (W1 * scale), "U", UColour, labelVerbosity, true, false, false);
        }

        // display behind rotor
        Vec middleTriangleOrigin = rotorTrailingEdge + (V2 * scale* offsetFromLE);
        (W2 * scale).PlotLine(middleTriangleOrigin, "W2", WOutColour, labelVerbosity, true, bDisplayAngles, false);
        if (triangleDisplayLevel > 2)
        {
            (V2 * scale).PlotLine(middleTriangleOrigin, "V2", VOutColour, labelVerbosity, true, bDisplayAngles, false);
            (U * scale).PlotLine(middleTriangleOrigin + (W2 * scale), "U2", UOutColour, labelVerbosity, true, false, false);
        }

        // behind stator, based on outflow angle.
        if (triangleDisplayLevel > 1)
        {
            Vec endTriangleOrigin = statorTrailingEdge + (outflowVec * offsetFromLE);
            outflowVec.PlotLine(endTriangleOrigin, "Outflow", UOutColour, labelVerbosity, false, bDisplayAngles, false);
        }

    }

    
    
}
