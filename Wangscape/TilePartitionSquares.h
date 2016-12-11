#pragma once
#include "TilePartition.h"

void tile_partition_squares(TilePartition& regions,
                            std::vector<TerrainID> corners,
                            const Options& options);