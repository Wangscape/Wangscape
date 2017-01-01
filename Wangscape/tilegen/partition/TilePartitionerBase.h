#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "../../Options.h"

class TilePartitionerBase
{
public:
    typedef std::vector<std::pair<sf::Texture, TerrainID>> TilePartition;
    typedef std::vector<TerrainID> Corners;

    explicit TilePartitionerBase(const Options& options);
    virtual ~TilePartitionerBase() = default;
    virtual void makePartition(TilePartition& regions, const Corners& corners) = 0;
protected:
    const Options& mOptions;
};