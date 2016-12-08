#pragma once
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "TileGenerator.h"
#include "TerrainImages.h"
class TilesetGenerator
{
public:
    TilesetGenerator(const Options& options);
    ~TilesetGenerator();
    void generate();
    void generateClique(const Options::Clique& clique, sf::RenderTexture& image,
                        TileGenerator::TileGenerateFunction callback);
    const Options& options;
    TerrainImages images;
};

