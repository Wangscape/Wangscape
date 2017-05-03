#include "Tileset.h"

namespace metaoutput
{

Tileset::Tileset(std::string filename_, sf::Vector2u resolution_, size_t x_, size_t y_, std::vector<TerrainID> terrains_)
    : filename(filename_), resolution(resolution_), x(x_), y(y_), terrains(terrains_)
{
}

} // namespace metaoutput
