#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "Options.h"

typedef std::vector<std::pair<sf::Texture, Options::TerrainID>> TilePartition;

typedef std::function<void(TilePartition&, std::vector<Options::TerrainID>, const Options&)> TilePartitionGenerator;