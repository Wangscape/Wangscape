#include "TerrainImages.h"
#include <boost/filesystem.hpp>



TerrainImages::TerrainImages()
{
}


TerrainImages::~TerrainImages()
{
}

void TerrainImages::addTerrain(Options::TerrainID tid, std::string image_filename, std::string json_filename,
                               size_t offset_x, size_t offset_y, size_t resolution)
{
    std::string filename = image_filename;
    boost::filesystem::path p(json_filename);
    p.remove_filename();
    p.append(filename);
    filename = p.string();
    auto it = source_images.find(filename);
    if (it == source_images.end())
    {
        sf::Image img;
        if (!img.loadFromFile(filename))
            throw std::runtime_error("Couldn't read image");
        it = source_images.insert({ filename, img }).first;
    }
    sf::Vector2i offset(offset_x, offset_y);
    sf::Vector2i box(resolution, resolution);
    offset *= (int)resolution;
    sf::Texture tex;
    if (!tex.loadFromImage((*it).second, sf::IntRect(offset, box)))
        throw std::runtime_error("Couldn't make texture from image");
    terrain_textures.insert({ tid, tex });
}
