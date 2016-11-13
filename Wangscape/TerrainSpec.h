#pragma once
#include <string>
struct TerrainSpec
{
    TerrainSpec(const std::string& full_name,
                const std::string& short_name,
                const std::string& file_name,
                unsigned int offset_x,
                unsigned int offset_y):
        fullName(full_name),
        shortName(short_name),
        fileName(file_name),
        offsetX(offset_x),
        offsetY(offset_y)
    {

    }
    std::string fullName;
    std::string shortName;
    std::string fileName;
    unsigned int offsetX;
    unsigned int offsetY;
};

