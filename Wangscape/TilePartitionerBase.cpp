#include "TilePartitionerBase.h"

void TilePartitionerBase::applyWeights(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas)
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
    while (err > 0)
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

TilePartitionerBase::TilePartitionerBase(const Options & options) :
    mOptions(options)
{
}

TilePartitionerBase::~TilePartitionerBase()
{
}