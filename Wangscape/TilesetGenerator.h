#pragma once
#include "Options.h"
#include "TileGenerator.h"
#include <boost/gil/gil_all.hpp>
class TilesetGenerator
{
public:
    TilesetGenerator();
    ~TilesetGenerator();
    static void generate(const Options& options);
    static void generateClique(const Options& options, const Options::Clique& clique,
                               void* image, TileGenerator::TileGenerateFunction callback);
};

