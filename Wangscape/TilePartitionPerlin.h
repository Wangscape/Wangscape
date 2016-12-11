#pragma once
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "BorderInfo.h"

#include "TilePartition.h"

void make_corner(TilePartition& regions, std::vector<TerrainID> corners,
                 bool left, bool top,
                 const BorderInfo& borders,
                 const Options& options);

void tile_partition_perlin(TilePartition& regions,
                           std::vector<TerrainID> corners,
                           const BorderInfo& borders,
                           const Options& options);