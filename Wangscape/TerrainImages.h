#pragma once
#include "Options.h"
#include <SFML/Graphics.hpp>
class TerrainImages
{
public:
    std::map<Options::TerrainID, sf::Texture> terrain_textures;
    TerrainImages();
    ~TerrainImages();
    static void rearrangeTile(sf::Texture& t);
    void addTerrain(Options::TerrainID tid, std::string image_filename, std::string json_filename,
                    size_t offset_x, size_t offset_y, size_t resolution);
protected:
    std::map<std::string, sf::Image> source_images;
};

