#pragma once
#include "../Options.h"
#include "../TerrainImages.h"
#include <functional>
#include "partition/TilePartitionerBase.h"
#include <SFML/Graphics.hpp>

namespace tilegen
{

class TileGenerator
{
public:
    TileGenerator() = default;
    virtual ~TileGenerator() = default;
    static void generate(sf::RenderTexture& image, size_t x, size_t y,
                         std::vector<TerrainID> corners,
                         const TerrainImages& images,
                         const Options& options,
                         partition::TilePartitionerBase& tile_partitioner);

};

} // namespace tilegen
