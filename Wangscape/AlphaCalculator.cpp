#include "AlphaCalculator.h"
#include <algorithm>
#include <assert.h>
#include <numeric>

AlphaCalculator::~AlphaCalculator()
{
}

void AlphaCalculator::calculatePixelAlphaLinear(WeightVector& weights, AlphaVector& alphas)
{
    int alpha_remaining = 255;
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
        alpha_remaining -= alpha;
        alphas[i] = (sf::Uint8)alpha;
    }
    size_t nonzero_alphas = std::accumulate(
        alphas.cbegin(),
        alphas.cend(),
        (size_t)0,
        [](const size_t& acc, const sf::Uint8& alpha)
        {
            return alpha > 0 ? acc + 1 : acc;
        });
    assert(nonzero_alphas > 0);
    auto divmod = std::div(alpha_remaining, nonzero_alphas);
    assert(divmod.quot >= 0);
    int alphas_incremented = 0;
    for(auto& alpha : alphas)
    {
        if (alpha == 0)
            continue;
        alpha += divmod.quot;
        alpha_remaining -= divmod.quot;
        if (alphas_incremented < divmod.rem)
        {
            alpha++;
            alpha_remaining--;
            alphas_incremented++;
        }
    }
    assert(alpha_remaining == 0);
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
    std::transform(weights.begin(), weights.end(), weights.begin(), fn);
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
