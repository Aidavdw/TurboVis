// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#pragma once

struct ImFont;
struct ImVec4;

namespace TurboVis
{
    class Stage;
    class StageContext;

    void DisplayMainMenu(StageContext& stageContext);

    void DisplayManual();

    ImVec4 Desaturate(const ImVec4 source);
}
