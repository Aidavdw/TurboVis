// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#include "Stage.h"
#include "implot.h"
#include "TurboVis.h"

void TurboVis::Stage::UpdateStageCoefficients()
{
    ImGui::Begin("Stage Coefficients");

    if (ImGui::DragFloat(flowCoefficientRange.c_str(), &flowCoefficient, 0.01f, 0.01f, 4.0f, "phi = %.3f", ImGuiSliderFlags_AlwaysClamp)) { ProcessDutyCoefficients(); }
    if (ImGui::DragFloat(workCoefficientRange.c_str(), &workCoefficient, 0.01f, 0.01f, 4.0f, "psi = %.3f", ImGuiSliderFlags_AlwaysClamp)) { ProcessDutyCoefficients(); }
    if (ImGui::DragFloat(degreeOfReactionRange.c_str(), &degreeOfReaction, 0.01f, 0.0f, 1.0f, "r = %.3f", ImGuiSliderFlags_AlwaysClamp)) { ProcessDutyCoefficients(); }

    ImGui::Separator();
    if (ImGui::DragFloat(rotationalSpeedRange.c_str(), &rotationalSpeed, 0.1f, 1.f, 4000.0f, "U = %.3f", ImGuiSliderFlags_AlwaysClamp)) { ProcessDutyCoefficients(); }
    ImGui::End();
}

void TurboVis::Stage::DisplayVelocityTriangleValues()
{
    ImGui::Begin("Velocity Triangle Values dump");

    ImGui::LabelText("Vector, m/s", "(axial, tangential)");
    ImGui::LabelText("U", "(%.3f, %.3f)", U.tangentialComponent, U.axialComponent);
    ImGui::Separator();
    ImGui::Text("Incoming flow");
    ImGui::LabelText("W_in", "%.3f (%.3ft, %.3fa)", W1.Magnitude(), W1.tangentialComponent, W1.axialComponent);
    ImGui::LabelText("beta_1", "%.2f deg", W1.Angle());
    ImGui::LabelText("V_in", "%.3f (%.3ft, %.3fa)", V1.Magnitude(), V1.tangentialComponent, V1.axialComponent);
    ImGui::LabelText("alpha_1", "%.2f deg", V1.Angle());

    ImGui::Separator();
    ImGui::Text("Outgoing flow");
    ImGui::LabelText("W_out", "%.3f (%.3ft, %.3fa)", W2.Magnitude(), W2.tangentialComponent, W2.axialComponent);
    ImGui::LabelText("beta_2", "%.2f deg", W2.Angle());
    ImGui::LabelText("V_out", "%.3f (%.3ft, %.3fa)", V2.Magnitude(), V2.tangentialComponent, V2.axialComponent);
    ImGui::LabelText("alpha_2", "%.2f deg", V2.Angle());


    ImGui::End();
}

void TurboVis::Stage::PlotVelocityTriangles()
{
    if (!bShowVelocityTriangleWindow)
        return;

    static int labelVerbosity = 2;
    static bool bDisplayAngles = true;
    static bool bOverlayU = false;
    static bool bDisplayArrows = true;


    ImGui::Begin("Velocity Triangles");

    // Display visualisation options
    if (ImGui::TreeNode("Visualisation Options"))
    {
        ImGui::Text("Label detail level");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { labelVerbosity = (labelVerbosity > 0) ? labelVerbosity - 1 : labelVerbosity; }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { labelVerbosity = (labelVerbosity < 3) ? labelVerbosity + 1 : labelVerbosity; }

        ImGui::Checkbox("Display angles", &bDisplayAngles);
        ImGui::Checkbox("Overlay U", &bOverlayU);

        ImGui::TreePop();
    }

    if (ImPlot::BeginPlot("Velocity Triangles", ImVec2(-1, -1), ImPlotFlags_Equal))
    {
        ImPlot::SetupAxis(ImAxis_X1, "Tangential, t", ImPlotAxisFlags_None);
        ImPlot::SetupAxis(ImAxis_Y1, "Axial, a", ImPlotAxisFlags_Invert);
        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y1);

        Vec centrePointOffset;
        
        // If we're overlaying U, then set middle of the top points as the origin.
        if (bOverlayU)
        {
            centrePointOffset = (W1 + U - V2) * 0.5;
        }


        W1.PlotLine(centrePointOffset, "W1", WColour, labelVerbosity, true, bDisplayAngles, bDisplayArrows);
        V1.PlotLine(centrePointOffset, "V1", VColour, labelVerbosity, true, bDisplayAngles, bDisplayArrows);
        U.PlotLine(centrePointOffset + W1, "U", UColour, labelVerbosity, true, false, bDisplayArrows);

        W2.PlotLine(centrePointOffset * -1, "W2", WOutColour, labelVerbosity, false, bDisplayAngles, bDisplayArrows);
        V2.PlotLine(centrePointOffset * -1, "V2", VOutColour, labelVerbosity, false, bDisplayAngles, bDisplayArrows);
        U.PlotLine(centrePointOffset* -1 + W2, "U", UOutColour, labelVerbosity, false, false, bDisplayArrows);

        ImPlot::EndPlot();
    }


    ImGui::End();
}

void TurboVis::Stage::DisplayAirfoils()
{
    if (!bShowAirfoilPlotWindow)
        return;

    static int labelVerbosity = 1;
    static bool bAllowAirfoilEdit = false;
    static int triangleDisplayLevel = 2;
    static bool bDisplayAngles = false;
    static bool bIsRepeatedStage = true;
    static float rotorPitch = 1.f;
    static float statorPitch = 1.f;
    static bool bAnimate = true;

    ImGui::Begin("Airfoil");

    ImGui::Text("Inline velocity triangles are scaled relative to V1.");

    ImGui::Checkbox("Is repeated stage?", &bIsRepeatedStage);
    ShowFlowAngleSettings(bIsRepeatedStage);

    if (ImGui::TreeNode("Visualisation Options"))
    {
        ImGui::Text("Label detail level");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { labelVerbosity = (labelVerbosity > 0) ? labelVerbosity - 1 : labelVerbosity; }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { labelVerbosity = (labelVerbosity < 1) ? labelVerbosity + 1 : labelVerbosity;;
        }

        ImGui::Text("Velocity triangle display detail level");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##left2", ImGuiDir_Left)) { triangleDisplayLevel = (triangleDisplayLevel > 0) ? triangleDisplayLevel - 1 : triangleDisplayLevel; }
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right2", ImGuiDir_Right)) { triangleDisplayLevel = (triangleDisplayLevel < 3) ? triangleDisplayLevel + 1 : triangleDisplayLevel; }


        ImGui::Checkbox("Edit Airfoil", &bAllowAirfoilEdit);
        ImGui::Checkbox("Display angles", &bDisplayAngles);
        ImGui::Checkbox("Rotation animation", &bAnimate);

        ImGui::Separator();
        
        ImGui::DragFloat("Rotor Pitch", &rotorPitch, 0.01f, 0.f, 5.0f, "d_rot = %.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::DragFloat("Stator Pitch", &statorPitch, 0.01f, 0.f, 5.0f, "d_stat = %.3f", ImGuiSliderFlags_AlwaysClamp);
        

        ImGui::TreePop();
    }


    if (ImPlot::BeginPlot("##Bezier", ImVec2(-1, -1), ImPlotFlags_Equal)) {
        ImPlot::SetupAxis(ImAxis_X1, "Tangential, t", ImPlotAxisFlags_None);
        ImPlot::SetupAxis(ImAxis_Y1, "Axial, a", ImPlotAxisFlags_Invert);
        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y1);

        DrawAirfoilPlot(labelVerbosity, bAllowAirfoilEdit, triangleDisplayLevel, rotorPitch, statorPitch, bDisplayAngles, bAnimate);

        /* Setting up the other parts of the plot*/
        // Repeated stage means that flow in must equal flow out; For a turbine, a0 = a2, for a comp, a1 = a3.

        ImPlot::EndPlot();
        
    }
    ImGui::End();
}

TurboVis::Vec TurboVis::Stage::AddAirfoilToPlot(const std::string& label, const Vec leadingEdge, const Vec Inflow, const Vec Outflow, ImPlotPoint& trailingEdgePoint, ImPlotPoint& curvatureControl, const int labelVerbosity, const bool bAllowAirfoilEdit, const float bladePitch, const float animationFrac, int baseID)
{
    ImPlotDragToolFlags flags = ImPlotDragToolFlags_None | ImPlotDragToolFlags_Delayed;

    // Trailing edge position is to be set by user!
    //static ImPlotPoint trailingEdgePoint = ImPlotPoint(0.0f, 2.f);
    if (bAllowAirfoilEdit)
        ImPlot::DragPoint(baseID+0, &trailingEdgePoint.x, &trailingEdgePoint.y, ImVec4(0, 0.9f, 0, 1), 4, flags);
    Vec trailingEdge = Vec(trailingEdgePoint.y, trailingEdgePoint.x);

    if (labelVerbosity > 2)
    {
        ImPlot::PlotText("Leading Edge", leadingEdge.tangentialComponent, leadingEdge.axialComponent);
        ImPlot::PlotText("Trailing Edge", trailingEdge.tangentialComponent, trailingEdge.axialComponent);
    }

    // Create pseudo control handle. The x value determines the length of the W1 influence, the y value the length of the W2 influence.
    //static ImPlotPoint curvatureControl = ImPlotPoint(-1.f, 1.f);
    ImPlotPoint previousPoint = curvatureControl;
    if (bAllowAirfoilEdit)
        ImPlot::DragPoint(baseID+1, &curvatureControl.x, &curvatureControl.y, ImVec4(0, 0.9f, 0, 1), 4, flags);
    Vec InflowExpansion = (Inflow * (1 / Inflow.Magnitude()) * (curvatureControl.x - leadingEdge.tangentialComponent) * -1) + leadingEdge;
    Vec OutflowExpansion = (Outflow * (1 / Outflow.Magnitude()) * (curvatureControl.y - trailingEdge.axialComponent)) + trailingEdge;


    // Clamping the control handle. Based on the fact that the expansions must be larger than 0, and also cannot extend further than the length of the airfoil.
    if (InflowExpansion.axialComponent > trailingEdge.axialComponent)
        curvatureControl.x = previousPoint.x; // Remember that the plot is flipped!
    if (InflowExpansion.axialComponent < leadingEdge.axialComponent)
        curvatureControl.x = previousPoint.x;

    if (OutflowExpansion.axialComponent < leadingEdge.axialComponent)
        curvatureControl.y = previousPoint.y;
    if (OutflowExpansion.axialComponent > trailingEdge.axialComponent)
        curvatureControl.y = previousPoint.y;

    // If blade pitch is 0, just draw one blade, otherwise just draw 11. 
    const int amountOfBlades = (bladePitch < 0.01f) ? 1 : 11;
    for (int i = 0; i < amountOfBlades; i++)
    {
        // Offset based on the blade position, but also on the animation cycle!
        float xOffset = (i-amountOfBlades/2 + animationFrac) * bladePitch;

        // Plotting the bezier
        ImPlotPoint P[] = {
            ImPlotPoint(leadingEdge.tangentialComponent + xOffset,leadingEdge.axialComponent), // LE
            ImPlotPoint(InflowExpansion.tangentialComponent + xOffset, InflowExpansion.axialComponent), // control of LE
            ImPlotPoint(OutflowExpansion.tangentialComponent + xOffset, OutflowExpansion.axialComponent), // control of TE
            ImPlotPoint(trailingEdge.tangentialComponent + xOffset, trailingEdge.axialComponent) // TE
        };

#define BEZIER_RESOLUTION 25

        ImPlotPoint B[BEZIER_RESOLUTION];
        for (int i = 0; i < BEZIER_RESOLUTION; ++i) {
            double t = static_cast<float>(i) / (BEZIER_RESOLUTION - 1);
            double u = 1 - t;
            double w1 = u * u * u;
            double w2 = 3 * u * u * t;
            double w3 = 3 * u * t * t;
            double w4 = t * t * t;

            double xtot = w1 * P[0].x + w2 * P[1].x + w3 * P[2].x + w4 * P[3].x;
            double ytot = w1 * P[0].y + w2 * P[1].y + w3 * P[2].y + w4 * P[3].y;
            B[i] = ImPlotPoint(xtot, ytot);
        }

        ImPlot::SetNextLineStyle(ImVec4(0.9f, 0.9f, 0.9f, 1), 4);
        ImPlot::PlotLine(label.c_str(), &B[0].x, &B[0].y, BEZIER_RESOLUTION, 0, sizeof(ImPlotPoint));
    }

    if (bAllowAirfoilEdit)
    {
        //ImPlot::SetNextLineStyle(ImVec4(1, 0.5f, 1, 1));
        //ImPlot::PlotLine("Control Handle", &P[0].x, &P[0].y, 2, 0, sizeof(ImPlotPoint));
        //ImPlot::SetNextLineStyle(ImVec4(0, 0.5f, 1, 1));
        //ImPlot::PlotLine("Control Handle", &P[2].x, &P[2].y, 2, 0, sizeof(ImPlotPoint));
    }


    return trailingEdge;

}

void TurboVis::Stage::DisplayWorkAndEnthalpy()
{





    ImGui::Begin("Thermodynamic Properties");
    if (ImGui::DragFloat("Specific Heat Ratio", &specificHeatRatio, 0.01f, 0.01f, 10.0f, "gamma = %.3f", ImGuiSliderFlags_None))
    {
    
    }

    if (ImGui::DragFloat("Specific Gas Constant", &specificGasConstant, 0.01f, 5.f, 1000.0f, "R = %.1f J/kg/K", ImGuiSliderFlags_None))
    {

    }

    if (ImGui::DragFloat("Flow Inlet Temperature", &inletTemperature, 0.01f, 5.f, 3000.0f, "T_in = %.1f K", ImGuiSliderFlags_None))
    {

    }

    // Definition of work coefficient psi
    deltavTangential = workCoefficient * rotationalSpeed;
    ImGui::LabelText("delta v_t", "%.3f", deltavTangential);

    deltaEnthalpy = deltavTangential * rotationalSpeed; // is the specific work!
    deltaEnthalpyRotor = deltaEnthalpy * degreeOfReaction; // Definition of R
    float deltaEnthalpyStator = deltaEnthalpy - deltaEnthalpyRotor;
    ImGui::LabelText("Specific work, change in enthalpy", "%.3f J", deltaEnthalpy);
    ImGui::LabelText("Rotor Specific Work", "%.3f J", deltaEnthalpyRotor);
    ImGui::LabelText("Stator specific Work", "%.3f J", deltaEnthalpyStator);


    // Stuff from the dimensionless euler equation
    tipSpeedMachNumber = sqrt(U.tangentialComponent * U.tangentialComponent / (specificGasConstant * specificHeatRatio * inletTemperature));
    ImGui::LabelText("Tip Speed Mach Number", "%.3f", tipSpeedMachNumber);

    float pressureRatio_pre = workCoefficient * tipSpeedMachNumber * tipSpeedMachNumber * (specificHeatRatio - 1) + 1;
    float pressureRatioExponent = specificHeatRatio / (specificHeatRatio - 1);
    float pressureRatio = pow(pressureRatio_pre, pressureRatioExponent);
    ImGui::LabelText("Pressure Ratio (total-to-total)", "%.3f", pressureRatio);

    ImGui::End();
}