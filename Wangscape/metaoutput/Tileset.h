#pragma once

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "common.h"

namespace metaoutput
{

struct Tileset
{
    Tileset() = default;
    Tileset(std::string filename_, sf::Vector2u resolution_, size_t x_, size_t y_, std::vector<TerrainID> terrains_);
    std::string filename;
    sf::Vector2u resolution;
    size_t x;
    size_t y;
    std::vector<TerrainID> terrains;
};

} // namespace metaoutput
