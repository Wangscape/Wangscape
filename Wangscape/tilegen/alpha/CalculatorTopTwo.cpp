#include "CalculatorTopTwo.h"

#include <algorithm>
#include <cassert>

namespace tilegen
{
namespace alpha
{
CalculatorTopTwo::TopTwoInfo CalculatorTopTwo::calculateTopTwoInfo(const Weights & weights)
{
    TopTwoInfo result;
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
    result.winner = winner.second;
    result.runner_up = runner_up.second;
    if (margin_sum <= 255 * std::numeric_limits<double>::epsilon())
        result.ratio = 1.;
    else
        result.ratio = runner_up_margin / margin_sum;
    // the winner : runner_up ratio is 1 : r
    return result;
}
void CalculatorTopTwo::updateAlphasAux(const Weights& weights)
{
    TopTwoInfo top_two_info = calculateTopTwoInfo(weights);

    if (top_two_info.ratio == 1.)
    {
        getAlpha(top_two_info.winner) = 128;
        getAlpha(top_two_info.runner_up) = 127;
        return;
    }
    else
    {
        double runner_up_scaled = pow(top_two_info.ratio, power);
        sf::Uint8 runner_up_share = std::max(0, std::min(255, int((255. * runner_up_scaled) / (1. + runner_up_scaled))));
        getAlpha(top_two_info.winner) = 255 - runner_up_share;
        getAlpha(top_two_info.runner_up) = runner_up_share;
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
