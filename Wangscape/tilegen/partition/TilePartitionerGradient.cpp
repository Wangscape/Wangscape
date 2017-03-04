#include "TilePartitionerGradient.h"
#include "tilegen/alpha/CalculatorLinear.h"
#include <utility>

namespace tilegen
{
namespace partition
{

int TilePartitionerGradient::gradientWeight(sf::Vector2u xy, sf::Vector2u corner, sf::Vector2u margin)
{
    sf::Vector2i distance = {std::abs((int)xy.x - (int)corner.x), std::abs((int)xy.y - (int)corner.y)};
    sf::Vector2i size = sf::Vector2i(mOptions.tileFormat.resolution) - sf::Vector2i(margin);
    sf::Vector2i values = size - distance;
    return std::max({0, values.x, values.y});
}

void TilePartitionerGradient::makePartition(TilePartition & regions,
                                            const Corners& corners)
{
    std::vector<sf::Image> masks;
    for (auto corner : corners)
    {
        sf::Image img;
        img.create(mOptions.tileFormat.resolution.x,
                   mOptions.tileFormat.resolution.y);
        masks.push_back(img);
    }
    std::vector<double> weights(corners.size(), 0.);
    const sf::Vector2u resolution_sub_1 = mOptions.tileFormat.resolution - sf::Vector2u(1,1);
    const sf::Vector2u quarter_res = mOptions.tileFormat.resolution / (unsigned int)4;
    alpha::CalculatorLinear ac;
    for (unsigned int x = 0; x < mOptions.tileFormat.resolution.x; x++)
    {
        for (unsigned int y = 0; y < mOptions.tileFormat.resolution.y; y++)
        {
            weights[0] = static_cast<double>(gradientWeight({x, y}, {0, 0}, quarter_res));
            weights[1] = static_cast<double>(gradientWeight({x, y}, {0, resolution_sub_1.y}, quarter_res));
            weights[2] = static_cast<double>(gradientWeight({x, y}, {resolution_sub_1.x, 0}, quarter_res));
            weights[3] = static_cast<double>(gradientWeight({x, y}, {resolution_sub_1.x, resolution_sub_1.y}, quarter_res));
            ac.updateAlphas(weights);
            const auto& alphas = ac.getAlphas();
            for (size_t i = 0; i < masks.size(); i++)
            {
                masks[i].setPixel(x, y, sf::Color(255, 255, 255, alphas[i]));
            }
        }
    }

    for (size_t i = 0; i < corners.size(); i++)
    {
        sf::Texture t;
        t.loadFromImage(masks[i]);
        regions.push_back({t, corners[i]});
    }
}

} // namespace partition
} // namespace tilegen
