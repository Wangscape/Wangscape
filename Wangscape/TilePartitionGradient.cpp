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
        int alpha = (int)((255 * weights[i]) / total_weight);
        err -= alpha;
        alphas[i] = (sf::Uint8)alpha;
    }
    size_t i = 0;
    while(err > 0)
    {
        sf::Uint8& alpha = alphas[i%alphas.size()];
        if (alpha > 0)
        {
            alpha++;
            err--;
        }
        i++;
    }
}

int gradient_weight(int x, int y, int X, int Y, int resolution_sub_1, int range)
{
    return std::max(0,(resolution_sub_1 - range - std::max(std::abs(x - X), std::abs(y - Y))));
}

void tile_partition_gradient(TilePartition & regions, std::vector<TerrainID> corners, const Options & options)
{
    std::vector<sf::Image> masks;
    for (auto corner : corners)
    {
        sf::Image img;
        img.create(options.tileFormat.resolution, options.tileFormat.resolution);
        masks.push_back(img);
    }
    std::vector<float> weights(corners.size(),0.f);
    std::vector<sf::Uint8> alphas(corners.size(), 0);
    int resolution_sub_1 = options.tileFormat.resolution - 1;
    for (size_t x = 0; x < options.tileFormat.resolution; x++)
    {
        for (size_t y = 0; y < options.tileFormat.resolution; y++)
        {
            weights[0] = (float)gradient_weight(x, y, 0, 0, resolution_sub_1, options.tileFormat.resolution / 4);
            weights[1] = (float)gradient_weight(x, y, 0, resolution_sub_1, resolution_sub_1, options.tileFormat.resolution / 4);
            weights[2] = (float)gradient_weight(x, y, resolution_sub_1, 0, resolution_sub_1, options.tileFormat.resolution / 4);
            weights[3] = (float)gradient_weight(x, y, resolution_sub_1, resolution_sub_1, resolution_sub_1, options.tileFormat.resolution / 4);
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
