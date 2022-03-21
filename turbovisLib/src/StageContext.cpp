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
        std::cout << "Switching to Compressor";
        stage = std::make_unique<AxialCompressor>();
        break;
    case 1:
        std::cout << "Changing to Turbine";
        stage = std::make_unique<AxialTurbine>();
        break;
    }
}
