#pragma once
#include "Options.h"
#include "TileGenerator.h"
class TilesetGenerator
{
public:
    TilesetGenerator(const Options& options);
    ~TilesetGenerator();
    void generate();
    void generateClique(const Options::Clique& clique,
                               void* image, TileGenerator::TileGenerateFunction callback);
    const Options& options;
protected:
    std::map<std::string, void*> terrain_images;
    std::map<Options::TerrainID, void*> terrain_image_views;
};

