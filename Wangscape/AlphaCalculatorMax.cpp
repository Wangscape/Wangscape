#include "AlphaCalculatorMax.h"
#include <algorithm>

void AlphaCalculatorMax::calculateAlphasAux(const Weights& weights, Alphas& alphas) const
{
    auto max_it = std::max_element(weights.cbegin(), weights.cend());
    auto max_index = std::distance(weights.cbegin(), max_it);
    auto alpha_it = alphas.begin();
    std::advance(alpha_it, max_index);
    *alpha_it = 255;
}
