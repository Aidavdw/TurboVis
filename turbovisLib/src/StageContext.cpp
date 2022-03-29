// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#include "StageContext.h"

#include <iostream>
#include <memory>

#include "AxialCompressor.h"
#include "AxialTurbine.h"

void TurboVis::StageContext::SetType(const int type)
{
    switch (type)
    {
    case 0:
        stage = std::make_unique<AxialCompressor>();
        break;
    case 1:
        stage = std::make_unique<AxialTurbine>();
        break;
    }
}
