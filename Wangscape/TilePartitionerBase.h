#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "Options.h"

class TilePartitionerBase
{
public:
    typedef std::vector<std::pair<sf::Texture, TerrainID>> TilePartition;
    typedef std::vector<TerrainID> Corners;

    TilePartitionerBase(const Options& options);
    virtual ~TilePartitionerBase();
    virtual void makePartition(TilePartition& regions, const Corners& corners) = 0;
    static void applyWeights(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas);
protected:
    const Options& mOptions;
};