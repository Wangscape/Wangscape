#pragma once

#include <string>
#include <vector>

namespace metaoutput
{

struct Tile
{
    Tile() = default;
    Tile(std::vector<std::string> corners_, std::string filename_, size_t x_, size_t y_);
    std::vector<std::string> corners;
    std::string filename;
    size_t x;
    size_t y;
};

} // namespace metaoutput
