#pragma once
#include "Options.h"
class TileGenerator
{
public:
    TileGenerator();
    ~TileGenerator();
    static void generate(void* image, size_t x, size_t y,
                         std::vector<std::string> terrains, const Options& options);
};

