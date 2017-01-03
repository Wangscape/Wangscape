#pragma once
#include <string>
struct TerrainSpec
{
    TerrainSpec() = default;
    TerrainSpec(const std::string& full_name,
                const std::string& file_name,
                unsigned int offset_x,
                unsigned int offset_y):
        fullName(full_name),
        fileName(file_name),
        offsetX(offset_x),
        offsetY(offset_y)
    {

    }
    std::string fullName;
    std::string fileName;
    unsigned int offsetX;
    unsigned int offsetY;
    virtual ~TerrainSpec() = default;
};

