#include "TileGenerator.h"
#include "TilePartitionSquares.h"
#include "TilePartitionGradient.h"



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
    TilePartition tp;
    //tile_partition_squares(tp, corners, options);
    tile_partition_gradient(tp, corners, options);
    sf::RenderTexture temp;
    temp.create(options.resolution, options.resolution);
    for (const auto& it : tp)
    {
        sf::Sprite tex(images.terrain_textures.at(it.second));
        temp.draw(tex, sf::RenderStates(sf::BlendNone));
        sf::Sprite mask(it.first);
        temp.draw(mask, sf::RenderStates(sf::BlendMultiply));
        temp.display();
        sf::Sprite tile(temp.getTexture());
        tile.setPosition(sf::Vector2f((float)x, (float)y)*(float)options.resolution);
        image.draw(tile, sf::RenderStates(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add,
                                                        sf::BlendMode::Zero, sf::BlendMode::One, sf::BlendMode::Add)));
        //image.draw(tile, sf::RenderStates(sf::BlendNone));
    }
}
