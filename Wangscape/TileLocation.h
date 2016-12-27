#pragma once

#include <string>

struct TileLocation
{
    TileLocation() = default;
    TileLocation(std::string filename_, size_t x_, size_t y_);
    std::string filename;
    size_t x;
    size_t y;
};
