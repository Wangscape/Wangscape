#include "CalculatorLinear.h"
#include <algorithm>
#include <assert.h>
#include <numeric>

namespace tilegen
{
namespace alpha
{

void CalculatorLinear::updateAlphasAux(const Weights& weights)
{
    int alpha_remaining = 255;
    double total_weight = std::accumulate(weights.cbegin(), weights.cend(), 0.);
    if (total_weight <= std::numeric_limits<double>::epsilon() * 255 * 4)
    {
        // This shouldn't happen, but it is easy to make weight masks
        // where this does happen.
        return;
    }
    // Underestimate the amount of alpha that can be assigned to each corner.
    for (size_t i = 0; i < weights.size(); i++)
    {
        int alpha = (int)((255 * weights[i]) / total_weight);
        alpha_remaining -= alpha;
        getAlpha(i) = (sf::Uint8)alpha;
    }
    // If all the alpha is assigned, skip the last part.
    if (alpha_remaining == 0)
        return;
    // Count the number of corners that have nonzero alpha.
    size_t nonzero_alphas = std::accumulate(
        getAlphas().cbegin(),
        getAlphas().cend(),
        (size_t)0,
        [](const size_t& acc, const sf::Uint8& alpha)
    {
        return alpha > 0 ? acc + 1 : acc;
    });
    assert(nonzero_alphas > 0);
    // Divide the remaining few alpha points as evenly as possible
    // between the nonzero corners.
    auto divmod = std::div(alpha_remaining, nonzero_alphas);
    assert(divmod.quot >= 0);
    int alphas_incremented = 0;
    for(size_t i = 0; i < getAlphas().size(); i++)
    {
        auto& alpha = getAlpha(i);
        if (alpha == 0)
            continue;
        alpha += divmod.quot;
        alpha_remaining -= divmod.quot;
        // The division may not be even.
        // In that case, some corners get one extra point.
        if (alphas_incremented < divmod.rem)
        {
            alpha++;
            alpha_remaining--;
            alphas_incremented++;
        }
    }
    assert(alpha_remaining == 0);
}

} // namespace alpha
} // namespace tilegen
