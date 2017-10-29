#include "TerrainImages.h"
#include <boost/filesystem.hpp>
#include <functional>

TerrainImages::TerrainImages(sf::Vector2u size)
{
    mTileRearrangement = rectangularRearrangement(makeVector(size));
}

void TerrainImages::rearrangeTile(sf::Image& base_tile)
{
    base_tile = mTileRearrangement.rearrangeTexture(base_tile);
}

void TerrainImages::addTerrain(TerrainID tid, std::string image_filename, std::string json_filename,
                               size_t offset_x, size_t offset_y, sf::Vector2u resolution)
{
    std::string filename = image_filename;
    // TODO(serin-delaunay): use mOptions.directory
    boost::filesystem::path p(json_filename);
    p.remove_filename();
    p.append(filename);
    filename = p.string();
    auto it = mSourceImages.find(filename);
    if (it == mSourceImages.end())
    {
        sf::Image img;
        if (!img.loadFromFile(filename))
            throw std::runtime_error("Couldn't read image");
        it = mSourceImages.insert({ filename, img }).first;
    }
    const sf::Vector2i offset(offset_x, offset_y);
    sf::Image tile;
    tile.create(resolution.x, resolution.y);
    tile.copy(it->second, 0,0, sf::IntRect(offset, sf::Vector2i(resolution)));
    rearrangeTile(tile);
    sf::Texture tex;
    if (!tex.loadFromImage(tile))
        throw std::runtime_error("Couldn't make texture from image");
    terrain_textures.insert({ tid, tex });
}
