#pragma once

#include "Vec.h"
#include <vector>
#include <string>
#include "imgui.h"
#include "implot.h"


namespace TurboVis
{
    class Stage
    {
    public:
        Stage() = default;

        Stage(const float flowCoefficient, const float workCoefficent, const float degreeOfReaction, const float rotationalSpeed) :
            flowCoefficient(flowCoefficient),
            workCoefficient(workCoefficent),
            degreeOfReaction(degreeOfReaction),
            rotationalSpeed(rotationalSpeed)
        {};

    public:

        bool bShowVelocityTriangleWindow = true;
        bool bShowAirfoilPlotWindow = true;

        ImVec4 UColour;
        ImVec4 VColour;
        ImVec4 WColour;
        ImVec4 UOutColour;
        ImVec4 VOutColour;
        ImVec4 WOutColour;

    protected:
        // Speed at which the rotor moves in the tangential direction: U
        float rotationalSpeed;

        // The ratio of axial velocity versus rotational velocity; phi = V_x / U
        float flowCoefficient;

        // The specific work performed by the turbomachine. Also the (Delta V_t) / U
        float workCoefficient;

        // Measure of the distribution (ratio) of the work between the rotor and the stator, r
        float degreeOfReaction;

        /* Velocity triangles */

        // Velocity triangle U
        Vec U;
        // Velocity triangle W1
        Vec W1;
        // Velocity triangle V1
        Vec V1;
        // Velocity triangle W2
        Vec W2;
        // Velocity triangle V2
        Vec V2;

        // The inflow of the stator
        float stageInflowAngle = 0;

        // the outflow angle of the stator
        float stageOutflowAngle = 0;

        /* For displaying the airfoil plots */


    public:
        /* Displays a window with fields for the stage coefficients, and updates the values accordingly.*/
        void UpdateStageCoefficients();

        /* Shows (debug) values of the velocity triangles in a window*/
        void DisplayVelocityTriangleValues();

        void PlotVelocityTriangles();

        // Displays the windows showing the airfoils. Depends on child implementation of ShowFlowAngleSettings(), DrawAirfoilPlot().
        void DisplayAirfoils();

        virtual void CalculateVelocityTriangles();

    protected:
        // Plots the rotor in PlotAirfoil();
        Vec AddAirfoilToPlot(const std::string& label, const Vec leadingEdge, const Vec Inflow, const Vec Outflow, ImPlotPoint& trailingEdgePoint, ImPlotPoint& curvatureControl, const int labelVerbosity, const bool bAllowAirfoilEdit, const float bladePitch, const float animationFrac = 0, int baseID = 0);

        // Shows the a0 & a3 flow angles. Different for types of stages, so defined in subclass.
        virtual void ShowFlowAngleSettings(bool bRepeatedStage);

        virtual void DrawAirfoilPlot(const int labelVerbosity, const bool bAllowAirfoilEdit, const int triangleDisplayLevel, const float rotorPitch, const float statorPitch, const bool bDisplayAngles, const bool bAnimate);
    };


}
