#pragma once
#include "TilePartition.h"
#include <SFML/Graphics.hpp>

void apply_weights(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas);

int gradient_weight(int x, int y, int X, int Y, int resolution_sub_1, int range=0);

void tile_partition_gradient(TilePartition& regions,
                             std::vector<TerrainID> corners,
                             const Options& options);