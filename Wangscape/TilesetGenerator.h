#pragma once
#include "Options.h"
#include <boost/gil/gil_all.hpp>
class TilesetGenerator
{
public:
    TilesetGenerator();
    ~TilesetGenerator();
    static bool generate(const Options& options);
};

