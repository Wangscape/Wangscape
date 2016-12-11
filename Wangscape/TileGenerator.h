#pragma once
#include "Options.h"
#include "TerrainImages.h"
#include <functional>
#include <SFML/Graphics.hpp>
class TileGenerator
{
public:
    TileGenerator();
    ~TileGenerator();
    typedef std::function<void(sf::RenderTexture&, size_t, size_t,
                               std::vector<TerrainID>,
                               const TerrainImages&,
                               const Options&)>
        TileGenerateFunction;
    static void generate(sf::RenderTexture& image, size_t x, size_t y,
                         std::vector<TerrainID> corners,
                         const TerrainImages& images,
                         const Options& options);

};

