#include "CalculatorTopTwo.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace tilegen
{
namespace alpha
{


void CalculatorTopTwo::updateAlphasAux(const Weights& weights)
{
    initialiseIndexedWeights(weights);
    std::sort(mIndexedWeights.begin(), mIndexedWeights.end(), std::greater<IndexedWeight>());
    const IndexedWeight& winner = mIndexedWeights[0];
    const IndexedWeight& runner_up = mIndexedWeights[1];
    const IndexedWeight& base = mIndexedWeights[2];

    double runner_up_margin = runner_up.first - base.first;
    double margin_sum = winner.first - base.first;
    assert(runner_up_margin >= 0.);
    assert(margin_sum >= 0.);
    assert(margin_sum >= runner_up_margin);
    if (margin_sum <= 255 * std::numeric_limits<double>::epsilon())
    {
        getAlpha(winner.second) = 128;
        getAlpha(runner_up.second) = 127;
        return;
    }
    else
    {
        double runner_up_scaled = std::pow(runner_up_margin / margin_sum, power);
        sf::Uint8 runner_up_share = std::max(0, std::min(255, int((255. * runner_up_scaled) / (1. + runner_up_scaled))));
        getAlpha(winner.second) = 255 - runner_up_share;
        getAlpha(runner_up.second) = runner_up_share;
    }
}

void CalculatorTopTwo::initialiseIndexedWeights(const Weights& weights)
{
    size_t count = 0;
    mIndexedWeights.resize(weights.size());
    std::transform(weights.cbegin(), weights.cend(),
                   mIndexedWeights.begin(),
                   [&count](double x)
    {
        return std::make_pair(x, count++);
    });
}

} // namespace alpha
} // namespace tilegen
