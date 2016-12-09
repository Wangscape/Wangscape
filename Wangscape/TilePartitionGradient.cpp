#include "TilePartitionGradient.h"
#include <utility>

void apply_weights(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas)
{
    int err = 255;
    float total_weight = 0.f;
    for (auto weight : weights)
        total_weight += weight;
    for (size_t i = 0; i < weights.size(); i++)
    {
        int alpha = (int)((256 * weights[i]) / total_weight);
        err -= alpha;
        if (i == weights.size() - 1)
            alpha += err;
        alphas[i] = (sf::Uint8)alpha;
    }
}

float gradient_weight(int x, int y, int X, int Y, int resolution_sub_1)
{
    return (float)(2 * resolution_sub_1 - std::max(std::abs(x - X), std::abs(y - Y)));
}

void tile_partition_gradient(TilePartition & regions, std::vector<Options::TerrainID> corners, const Options & options)
{
    std::vector<sf::Image> masks;
    for (auto corner : corners)
    {
        sf::Image img;
        img.create(options.resolution, options.resolution);
        masks.push_back(img);
    }
    std::vector<float> weights(corners.size(),0.f);
    std::vector<sf::Uint8> alphas(corners.size(), 0);
    int resolution_sub_1 = options.resolution - 1;
    for (size_t x = 0; x < options.resolution; x++)
    {
        for (size_t y = 0; y < options.resolution; y++)
        {
            weights[0] = gradient_weight(x, y, 0, 0, resolution_sub_1);
            weights[1] = gradient_weight(x, y, 0, resolution_sub_1, resolution_sub_1);
            weights[2] = gradient_weight(x, y, resolution_sub_1, 0, resolution_sub_1);
            weights[3] = gradient_weight(x, y, resolution_sub_1, resolution_sub_1, resolution_sub_1);
            apply_weights(weights, alphas);
            for (size_t i = 0; i < masks.size(); i++)
            {
                masks[i].setPixel(x, y, sf::Color(255, 255, 255, alphas[i]));
            }
        }
    }

    for (size_t i=0; i<corners.size(); i++)
    {
        sf::Texture t;
        t.loadFromImage(masks[i]);
        regions.push_back({ t,corners[i] });
    }
}
