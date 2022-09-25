// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#include "TurboVis.h"
#include "imgui.h"
#include <memory>

#include "AxialCompressor.h"
#include "Stage.h"
#include "AxialTurbine.h"
#include "StageContext.h"


void TurboVis::DisplayMainMenu(StageContext& stageContext)
{
    ImGui::Begin("TurboVis ver 1.2");
    const char* availableTurbomachineTypes[] = { "Axial Compressor", "Axial Turbine"};
    static int currentTurbomachineType = 0;
    if (ImGui::Combo("Turbomachine type", &currentTurbomachineType, availableTurbomachineTypes, IM_ARRAYSIZE(availableTurbomachineTypes)))
    {
        stageContext.SetType(currentTurbomachineType);
    }

    ImGui::Checkbox("Show velocity triangle window", &stageContext.stage->bShowVelocityTriangleWindow);
    ImGui::Checkbox("Show airfoil window", &stageContext.stage->bShowAirfoilPlotWindow);

    ImGui::Separator();
    ImGui::Text("Options");
    static bool bUseLargeFont = false;
    if (ImGui::Checkbox("Use large font", &bUseLargeFont))
    {
        ImGui::GetFont()->Scale = 1.f - !bUseLargeFont * 0.4f;
    }

    // colour settings
    static float ucol[3] = { 0.42f, 0.78f, 0.11f };
    static float vcol[3] = { 0.6f, 0.134f, 0.747f };
    static float wcol[3] = { 0.71f, 0.09f, 0.09f };
    ImGui::ColorEdit3("Colour of U", ucol);
    ImGui::ColorEdit3("Colour of V", vcol);
    ImGui::ColorEdit3("Colour of W", wcol);
    stageContext.stage->UColour = ImVec4(ucol[0], ucol[1], ucol[2], 1.f);
    stageContext.stage->VColour = ImVec4(vcol[0], vcol[1], vcol[2], 1.f);
    stageContext.stage->WColour = ImVec4(wcol[0], wcol[1], wcol[2], 1.f);
    stageContext.stage->UOutColour = Desaturate(stageContext.stage->UColour);
    stageContext.stage->VOutColour = Desaturate(stageContext.stage->VColour);
    stageContext.stage->WOutColour = Desaturate(stageContext.stage->WColour);

    // Saving the current layout
    if (ImGui::Button("Save current layout"))
    {
        ImGui::SaveIniSettingsToDisk("turbovis.ini");
    }



    ImGui::End();
}

ImVec4 TurboVis::Desaturate(const ImVec4 source)
{
    return ImVec4(source.x / 1.6, source.y / 1.6, source.z/ 1.6, source.w);
}