#include "AlphaCalculatorBase.h"
#include <algorithm>

void AlphaCalculatorBase::calculateAlphas(const Weights & weights, Alphas & alphas) const
{
    for (auto& alpha : alphas)
        alpha = 0;
    calculateAlphasAux(weights, alphas);
}
