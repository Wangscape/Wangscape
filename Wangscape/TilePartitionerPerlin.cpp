#include "TilePartitionerPerlin.h"

void TilePartitionerPerlin::makeCorner(TilePartition & regions, const Corners& corners,
                                       bool left, bool top)
{
    TerrainID corner_id = corners[ (left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_h =  corners[(!left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_v =  corners[ (left ? 0 : 1) + (!top ? 0 : 2)];
    //BorderInfo::TerrainIDPair border_id_h(left ? corner_id : corner_h, left ? corner_h : corner_id);
    //BorderInfo::TerrainIDPair border_id_v(top ? corner_id : corner_v, top ? corner_v : corner_id);
    //const BorderInfo::UniqueModule& border_h = borders.borders.at(border_id_h).first;
    //const BorderInfo::UniqueModule& border_v = borders.borders.at(border_id_v).first;

}

void TilePartitionerPerlin::makePartition(TilePartition & regions, const Corners& corners)
{
    makeCorner(regions, corners, true, true);
    makeCorner(regions, corners, true, false);
    makeCorner(regions, corners, false, true);
    makeCorner(regions, corners, false, false);
    // for each corner:
    //   load x border details
    //   load y border details
    //   convert border details to deterministic mask
    //   make stochastic mask
    //   make/load combiner mask
    //   combine deterministic and stochastic masks according to combiner mask, making corner mask
    // post-processing steps
    // normalise corner masks so they add up to 255 everywhere
}

TilePartitionerPerlin::TilePartitionerPerlin(const Options & options) :
    TilePartitionerBase(options),
    mNoiseModuleManager(options)
{
}
