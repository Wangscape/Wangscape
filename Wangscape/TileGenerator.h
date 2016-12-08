#pragma once
#include "Options.h"
#include <functional>
class TileGenerator
{
public:
    TileGenerator();
    ~TileGenerator();
    typedef std::function<void(void*, size_t, size_t,
                               std::vector<Options::TerrainID>,
                               const Options&)>
        TileGenerateFunction;
    static void generate(void* image, size_t x, size_t y,
                         std::vector<Options::TerrainID> corners,
                         const Options& options);
};

