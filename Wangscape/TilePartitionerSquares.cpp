#include "TilePartitionerSquares.h"

void TilePartitionerSquares::makePartition(TilePartition& regions, const Corners& corners)
{
    sf::RectangleShape quarter_tile;
    const auto resolution = mOptions.resolution;
    quarter_tile.setSize(sf::Vector2f(resolution / 2.f, resolution / 2.f));
    quarter_tile.setFillColor(sf::Color::White);
    quarter_tile.setOutlineThickness(0.f);
    sf::RenderTexture mask;
    mask.create(resolution, resolution);

    auto make_mask = [&](sf::Vector2f origin, TerrainID tid)
    {
        mask.clear(sf::Color(255, 255, 255, 0));
        quarter_tile.setPosition(origin);
        mask.draw(quarter_tile);
        mask.display();
        sf::Texture t(mask.getTexture());
        regions.push_back({ t, tid });
    };
    make_mask(sf::Vector2f(0, 0), corners[0]);
    make_mask(sf::Vector2f(0, resolution / 2.f), corners[1]);
    make_mask(sf::Vector2f(resolution / 2.f, 0), corners[2]);
    make_mask(sf::Vector2f(resolution / 2.f, resolution / 2.f), corners[3]);
};


TilePartitionerSquares::TilePartitionerSquares(const Options & options) :
    TilePartitionerBase(options)
{
}
