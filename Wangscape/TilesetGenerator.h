#pragma once
#include "Options.h"
#include <boost/gil/gil_all.hpp>
class TilesetGenerator
{
public:
    TilesetGenerator();
    ~TilesetGenerator();
    static void generate(const Options& options,
                         std::function<void(void*, size_t, size_t,
                                            std::vector<Options::TerrainID>,
                                            const Options&)> callback);
};

