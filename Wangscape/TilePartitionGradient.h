#pragma once
#include "TilePartition.h"
#include <sfml/Graphics.hpp>

void apply_weights(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas);

float gradient_weight(int x, int y, int X, int Y, int resolution_sub_1);

void tile_partition_gradient(TilePartition& regions,
                             std::vector<Options::TerrainID> corners,
                             const Options& options);