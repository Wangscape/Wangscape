#pragma once

#include <string>
#include <utility>
#include "common.h"

struct BorderModuleGroupLocation
{
    std::pair<TerrainID, TerrainID> terrains;
    std::string filename;
};