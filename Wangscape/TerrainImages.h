#pragma once
#include "Options.h"
#include <SFML/Graphics.hpp>
#include "image/TileRearranger.h"

class TerrainImages
{
public:
    std::map<TerrainID, sf::Texture> terrain_textures;
    TerrainImages(sf::Vector2u size);
    virtual ~TerrainImages() = default;
    void rearrangeTile(sf::Image& base_tile);
    void addTerrain(TerrainID tid, std::string image_filename, std::string json_filename,
                    size_t offset_x, size_t offset_y, sf::Vector2u resolution);
private:
    std::map<std::string, sf::Image> mSourceImages;
    TileRearrangement mTileRearrangement;
};

