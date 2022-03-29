// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#include "Vec.h"
#include "implot.h"

float TurboVis::Vec::Magnitude() const
{
    return sqrtf(tangentialComponent * tangentialComponent + axialComponent * axialComponent);
}

float TurboVis::Vec::Angle() const
{
    return atanf(tangentialComponent / axialComponent) * 180.f / PI;
}

TurboVis::Vec TurboVis::Vec::GetNormalised() const
{
    return *this * (1/Magnitude());
}

void TurboVis::Vec::PlotLine(const Vec& origin, const std::string& label, const ImVec4 colour, int labelVerbosity, bool bFlipLabel, bool bDisplayAngle, const bool bDisplayArrows) const
{
    Vec endPos = origin + *this;
    float xs[2] = { origin.tangentialComponent, endPos.tangentialComponent };
    float ys[2] = { origin.axialComponent, endPos.axialComponent };

    Vec middlePoint = origin + *this * 0.5;

    ImPlot::SetNextLineStyle(colour, 4.f);
    ImPlot::PlotLine(label.c_str(), xs, ys, 2);

    // Generate the label text based on the verbosity level. Level 1 has just the name, level 2 has the magnitude, level 3 has the components.
    if (labelVerbosity > 0)
    {
        char labelBuffer[100] = "";
        switch (labelVerbosity)
        {
        case 2:
            snprintf(labelBuffer, sizeof(labelBuffer), "%s = %.4f", label.c_str(), Magnitude());
            break;
        case 3:
            snprintf(labelBuffer, sizeof(labelBuffer), "%s = %.4f\n(%.3ft, %.3fa)", label.c_str(), Magnitude(), tangentialComponent, axialComponent);
            break;
        default:
            snprintf(labelBuffer, sizeof(labelBuffer), "%s", label.c_str());
            break;
        }
        
        auto offset = bFlipLabel ? ImVec2(15, 15) : ImVec2(-15, -15);
        auto col = ImPlot::GetLastItemColor();
        ImPlot::Annotation(middlePoint.tangentialComponent, middlePoint.axialComponent, col, offset, true, labelBuffer);
    }


    if (bDisplayAngle)
    {
        // Display the angle!
        // Construct an arc between the axial axis and the point where the angle will be drawn.
#define ARCSEGMENTS 10
        int idx = label[1] - '0';
        float distanceRatio = 0.1f + idx * 0.2f;
        float radius = distanceRatio * Magnitude();

        Vec circleEndPoint = origin + *this * distanceRatio;
        Vec circleStartPoint = origin + Vec(radius, 0.f);

        float arcxs[ARCSEGMENTS], arcys[ARCSEGMENTS];
        for (int i = 0; i < ARCSEGMENTS; i++)
        {
            arcxs[i] = circleEndPoint.tangentialComponent + (circleStartPoint.tangentialComponent - circleEndPoint.tangentialComponent) / (ARCSEGMENTS - 1) * i;
            // Use some trig to get the corresponding y component
            arcys[i] = sqrtf(radius * radius - arcxs[i] * arcxs[i] - origin.tangentialComponent * origin.tangentialComponent + 2 * origin.tangentialComponent * arcxs[i]) + origin.axialComponent;
        }

        ImPlot::PlotLine("Angles", arcxs, arcys, ARCSEGMENTS);

        if (abs(Angle()) > 3 && labelVerbosity > 0)
        {
            // Also add the number
            char angleBuffer[20] = "";
            switch (label[0])
            {
            case 'V':
                if (labelVerbosity == 1)
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_%i", idx);
                else
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_%i\n%.2f deg", idx, Angle());
                break;
            case 'W':
                if (labelVerbosity == 1)
                    snprintf(angleBuffer, sizeof(angleBuffer), "beta_%i", idx);
                else
                    snprintf(angleBuffer, sizeof(angleBuffer), "beta_%i\n%.2f deg", idx, Angle());
                break;
            case 'O':
                if (labelVerbosity == 1)
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_3");
                else
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_3\n%.2f deg", Angle());
                break;
            case 'I':
                if (labelVerbosity == 1)
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_0");
                else
                    snprintf(angleBuffer, sizeof(angleBuffer), "alpha_0\n%.2f deg", Angle());
                break;
            }
            Vec centre = circleEndPoint * 0.5 + circleStartPoint * 0.5;
            ImPlot::PlotText(angleBuffer, centre.tangentialComponent, centre.axialComponent);
        }
    }
}
