#include "TilePartitionPerlin.h"

void tile_partition_perlin(TilePartition & regions, std::vector<TerrainID> corners, const Options & options)
{
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
