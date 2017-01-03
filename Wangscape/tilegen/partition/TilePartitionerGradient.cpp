#include "TilePartitionerGradient.h"
#include "tilegen/alpha/AlphaCalculatorLinear.h"
#include <utility>

namespace tilegen
{
namespace partition
{

int TilePartitionerGradient::gradientWeight(int x, int y, int x_corner, int y_corner, int margin)
{
    return std::max(0, ((int)mOptions.tileFormat.resolution - 1 - margin -
                        std::max(std::abs(x - x_corner),
                                 std::abs(y - y_corner))));
}

void TilePartitionerGradient::makePartition(TilePartition & regions,
                                            const Corners& corners)
{
    std::vector<sf::Image> masks;
    for (auto corner : corners)
    {
        sf::Image img;
        img.create(mOptions.tileFormat.resolution,
                   mOptions.tileFormat.resolution);
        masks.push_back(img);
    }
    std::vector<double> weights(corners.size(), 0.);
    const int resolution_sub_1 = mOptions.tileFormat.resolution - 1;
    const int quarter_res = mOptions.tileFormat.resolution / 4;
    alpha::AlphaCalculatorLinear ac;
    for (size_t x = 0; x < mOptions.tileFormat.resolution; x++)
    {
        for (size_t y = 0; y < mOptions.tileFormat.resolution; y++)
        {
            weights[0] = (double)gradientWeight(x, y, 0, 0, quarter_res);
            weights[1] = (double)gradientWeight(x, y, 0, resolution_sub_1, quarter_res);
            weights[2] = (double)gradientWeight(x, y, resolution_sub_1, 0, quarter_res);
            weights[3] = (double)gradientWeight(x, y, resolution_sub_1, resolution_sub_1, quarter_res);
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
