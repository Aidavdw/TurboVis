#pragma once

struct ImFont;
struct ImVec4;

namespace TurboVis
{
    class Stage;

    void DisplayMainMenu(Stage* stage);

    ImVec4 Desaturate(const ImVec4 source);

}
