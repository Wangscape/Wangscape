#include "TileGenerator.h"



TileGenerator::TileGenerator()
{
}


TileGenerator::~TileGenerator()
{
}

void TileGenerator::generate(sf::RenderTexture& image, size_t x, size_t y,
                             std::vector<Options::TerrainID> corners,
                             const TerrainImages& images,
                             const Options& options)
{
    x *= options.resolution;
    y *= options.resolution;
    sf::Vector2i quarter_tile(options.resolution / 2, options.resolution / 2);
    auto draw_corner = [&](size_t corner, int left, int top)
    {
        sf::Sprite s(images.terrain_textures.at(corners[corner]),
                     sf::IntRect({ left,top }, quarter_tile));
        s.setPosition((float)(x+left), (float)(y+top));
        image.draw(s);
    };
    draw_corner(0, 0, 0);
    draw_corner(1, 0, options.resolution / 2);
    draw_corner(2, options.resolution / 2, 0);
    draw_corner(3, options.resolution / 2, options.resolution / 2);
}
