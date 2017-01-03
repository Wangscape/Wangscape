#include "AlphaCalculatorMax.h"
#include <algorithm>

namespace tilegen
{
namespace alpha
{

void AlphaCalculatorMax::updateAlphasAux(const Weights& weights)
{
    auto max_it = std::max_element(weights.cbegin(), weights.cend());
    auto max_index = std::distance(weights.cbegin(), max_it);
    getAlpha(max_index) = 255;
}

} // namespace alpha
} // namespace tilegen
