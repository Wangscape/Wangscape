#include "AlphaCalculator.h"
#include <algorithm>
#include <numeric>



AlphaCalculator::AlphaCalculator()
{
}


AlphaCalculator::~AlphaCalculator()
{
}

void AlphaCalculator::calculatePixelAlphaLinear(WeightVector& weights, AlphaVector& alphas)
{
    int err = 255;
    float total_weight = 0.f;
    for (auto& weight : weights)
    {
        weight = std::max(0.f, weight);
        total_weight += weight;
    }
    if (total_weight <= 0.f)
    {
        // This shouldn't happen, but it is easy to make weight masks
        // where this does happen.
        for (auto& alpha : alphas)
        {
            alpha = 0;
        }
        return;
    }
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

void AlphaCalculator::calculatePixelAlphaMax(WeightVector& weights, AlphaVector& alphas)
{
    for (auto& alpha : alphas)
    {
        alpha = 0;
    }
    auto max_it = std::max_element(weights.cbegin(), weights.cend());
    auto max_idx = std::distance(weights.cbegin(), max_it);
    auto alpha_it = alphas.begin();
    std::advance(alpha_it, max_idx);
    *alpha_it = 255;
}

void AlphaCalculator::calculatePixelAlphaFunction(WeightVector& weights, AlphaVector& alphas,
                                                  std::function<float(float)> fn)
{
    for (auto& weight : weights)
    {
        weight = fn(weight);
    }
    calculatePixelAlphaLinear(weights, alphas);
}

AlphaCalculator::PixelAlphaCalculator AlphaCalculator::makeCalculatePixelAlphaPower(float power)
{
    return bindCalculatePixelAlphaFunction(std::bind(powf, std::placeholders::_1, power));
}

AlphaCalculator::PixelAlphaCalculator AlphaCalculator::bindCalculatePixelAlphaFunction(std::function<float(float)> fn)
{
    return std::bind(calculatePixelAlphaFunction, std::placeholders::_1, std::placeholders::_2, fn);
}
