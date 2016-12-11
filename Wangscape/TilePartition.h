#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "Options.h"

typedef std::vector<std::pair<sf::Texture, TerrainID>> TilePartition;

typedef std::function<void(TilePartition&, std::vector<TerrainID>, const Options&)> TilePartitionGenerator;