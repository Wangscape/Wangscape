#pragma once
#include <noise/noise.h>
#include <SFML/Graphics.hpp>

#include "TilePartition.h"

void tile_partition_perlin(TilePartition& regions,
                           std::vector<TerrainID> corners,
                           const Options& options);