#include "TileGenerator.h"
#include "partition/TilePartitionerBase.h"

namespace tilegen
{

void TileGenerator::generate(sf::RenderTexture& image, size_t x, size_t y,
                             std::vector<TerrainID> corners,
                             const TerrainImages& images,
                             const Options& options,
                             partition::TilePartitionerBase& tile_partitioner)
{
    partition::TilePartitionerBase::TilePartition tp;
    tile_partitioner.makePartition(tp, corners);
    sf::RenderTexture temp;
    temp.create(options.tileFormat.resolution, options.tileFormat.resolution);
    for (const auto& it : tp)
    {
        sf::Sprite tex(images.terrain_textures.at(it.second));
        temp.draw(tex, sf::RenderStates(sf::BlendNone));
        sf::Sprite mask(it.first);
        temp.draw(mask, sf::RenderStates(sf::BlendMultiply));
        temp.display();
        sf::Sprite tile(temp.getTexture());
        tile.setPosition(sf::Vector2f((float)x, (float)y)*(float)options.tileFormat.resolution);
        image.draw(tile, sf::RenderStates(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add,
                                                        sf::BlendMode::Zero,     sf::BlendMode::One, sf::BlendMode::Add)));
        //image.draw(tile, sf::RenderStates(sf::BlendNone));
    }
}

} // namespace tilegen
