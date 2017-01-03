#pragma once

#include <string>
#include <vector>

#include "common.h"

namespace metaoutput
{

struct Tileset
{
    Tileset() = default;
    Tileset(std::string filename_, size_t resolution_, size_t x_, size_t y_, std::vector<TerrainID> terrains_);
    std::string filename;
    size_t resolution;
    size_t x;
    size_t y;
    std::vector<TerrainID> terrains;
};

} // namespace metaoutput
