#pragma once

#include <string>
#include <vector>

#include "common.h"

struct Tileset
{
    std::string filename;
    size_t resolution;
    size_t x;
    size_t y;
    std::vector<TerrainID> terrains;
};
