#pragma once
#include "Options.h"
#include "TerrainImages.h"
#include <functional>
#include "TilePartitionerBase.h"
#include <SFML/Graphics.hpp>
class TileGenerator
{
public:
    TileGenerator() = default;
    virtual ~TileGenerator() = default;
    static void generate(sf::RenderTexture& image, size_t x, size_t y,
                         std::vector<TerrainID> corners,
                         const TerrainImages& images,
                         const Options& options,
                         TilePartitionerBase& tile_partitioner);

};

