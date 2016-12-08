#pragma once
#include "Options.h"
#include <functional>
#include <SFML/Graphics.hpp>
class TileGenerator
{
public:
    TileGenerator();
    ~TileGenerator();
    typedef std::function<void(sf::Image&, size_t, size_t,
                               std::vector<Options::TerrainID>,
                               const Options&)>
        TileGenerateFunction;
    static void generate(sf::Image& image, size_t x, size_t y,
                         std::vector<Options::TerrainID> corners,
                         const Options& options);
};

