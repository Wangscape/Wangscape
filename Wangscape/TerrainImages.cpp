#include "TerrainImages.h"
#include <boost/filesystem.hpp>
#include <functional>


TerrainImages::TerrainImages()
{
}


TerrainImages::~TerrainImages()
{
}

void TerrainImages::rearrangeTile(sf::Texture& t)
{
    auto resolution = t.getSize();
    sf::Vector2i origin(0, 0);
    sf::Vector2i middle(resolution.x / 2, resolution.y / 2);
    sf::RenderTexture new_tile;
    new_tile.create(resolution.x, resolution.y);
    sf::Sprite corner;
    corner.setTexture(t);
    auto draw_corner = [&](int from_x, int  from_y,
                           int to_x, int to_y)
    {
        // TODO odd tile sizes will definitely break this!
        corner.setTextureRect(sf::IntRect(from_x, from_y, middle.x, middle.y));
        corner.setPosition((float)to_x, (float)to_y);
        new_tile.draw(corner);
    };
    draw_corner(origin.x, origin.y, middle.x, middle.y);
    draw_corner(middle.x, middle.y, origin.x, origin.y);
    draw_corner(origin.x, middle.y, middle.x, origin.y);
    draw_corner(middle.x, origin.y, origin.x, middle.y);
    new_tile.display();
    t = new_tile.getTexture();
}

void TerrainImages::addTerrain(TerrainID tid, std::string image_filename, std::string json_filename,
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
    rearrangeTile(tex);
    terrain_textures.insert({ tid, tex });
}
