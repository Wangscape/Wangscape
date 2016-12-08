#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TerrainImages.h"
#include "Options.h"
class TilePartition
{
public:
    std::vector<std::pair<sf::Texture, Options::TerrainID>> regions;

    TilePartition(std::vector<Options::TerrainID> corners, const Options& options);
    ~TilePartition();
    virtual void initialise(std::vector<Options::TerrainID> corners, const Options& options) = 0;
protected:
};

