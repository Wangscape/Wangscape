#include "TilePartitionerGradient.h"
#include "../alpha/AlphaCalculatorLinear.h"
#include <utility>

int TilePartitionerGradient::gradientWeight(int x, int y, int x_corner, int y_corner, int margin)
{
    return std::max(0, ((int)mOptions.resolution - 1 - margin -
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
        img.create(mOptions.resolution, mOptions.resolution);
        masks.push_back(img);
    }
    std::vector<float> weights(corners.size(), 0.f);
    int resolution_sub_1 = mOptions.resolution - 1;
    AlphaCalculatorLinear ac;
    for (size_t x = 0; x < mOptions.resolution; x++)
    {
        for (size_t y = 0; y < mOptions.resolution; y++)
        {
            weights[0] = (float)gradientWeight(x, y, 0, 0, mOptions.resolution / 4);
            weights[1] = (float)gradientWeight(x, y, 0, resolution_sub_1, mOptions.resolution / 4);
            weights[2] = (float)gradientWeight(x, y, resolution_sub_1, 0, mOptions.resolution / 4);
            weights[3] = (float)gradientWeight(x, y, resolution_sub_1, resolution_sub_1, mOptions.resolution / 4);
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
