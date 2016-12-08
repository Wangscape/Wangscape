#pragma once
#include "TilePartition.h"
class TilePartitionSquares : public TilePartition
{
public:
    TilePartitionSquares(std::vector<Options::TerrainID> corners, const Options& options);
    virtual void initialise(std::vector<Options::TerrainID> corners, const Options& options);
};

