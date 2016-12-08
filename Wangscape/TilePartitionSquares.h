#pragma once
#include "TilePartition.h"

void tile_partition_squares(TilePartition& regions,
                            std::vector<Options::TerrainID> corners,
                            const Options& options);