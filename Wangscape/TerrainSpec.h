#pragma once
#include <string>
struct TerrainSpec
{
    TerrainSpec(const std::string& full_name,
                const std::string& file_name):
        fullName(full_name),
        fileName(file_name)
    {

    }
    std::string fullName;
    std::string fileName;
};

