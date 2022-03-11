#pragma once

struct ImFont;
struct ImVec4;

namespace TurboVis
{
    class Stage;
    class StageContext;

    void DisplayMainMenu(StageContext& stageContext);

    ImVec4 Desaturate(const ImVec4 source);
}
