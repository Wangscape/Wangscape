#include "TerrainImages.h"
#include <boost/filesystem.hpp>
#include <functional>

void TerrainImages::rearrangeTile(sf::Texture& t)
{
    auto resolution = t.getSize();
    sf::Vector2i origin(0, 0);
    sf::Vector2i middle(resolution.x / 2, resolution.y / 2);
    sf::Vector2i middle_to_end = sf::Vector2i(resolution) - middle;
    sf::RenderTexture new_tile;
    new_tile.create(resolution.x, resolution.y);
    sf::Sprite corner;
    corner.setTexture(t);
    auto draw_corner = [&](sf::Vector2i from,
                           sf::Vector2i to,
                           sf::Vector2i size)
    {
        corner.setTextureRect(sf::IntRect(from.x, from.y, size.x, size.y));
        corner.setPosition((float)to.x, (float)to.y);
        new_tile.draw(corner);
    };
    draw_corner(origin, middle, middle_to_end);
    draw_corner({origin.x, middle_to_end.y}, {middle.x, origin.y}, {middle_to_end.x, middle.y});
    draw_corner({middle_to_end.x, origin.y}, {origin.x, middle.y}, {middle.x, middle_to_end.y});
    draw_corner(middle_to_end, origin, middle);
    new_tile.display();
    t = new_tile.getTexture();
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
    auto it = source_images.find(filename);
    if (it == source_images.end())
    {
        sf::Image img;
        if (!img.loadFromFile(filename))
            throw std::runtime_error("Couldn't read image");
        it = source_images.insert({ filename, img }).first;
    }
    sf::Vector2i offset(offset_x, offset_y);
    sf::Texture tex;
    if (!tex.loadFromImage((*it).second, sf::IntRect(offset, sf::Vector2i(resolution))))
        throw std::runtime_error("Couldn't make texture from image");
    rearrangeTile(tex);
    terrain_textures.insert({ tid, tex });
}
