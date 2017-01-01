#include "AlphaCalculatorBase.h"
#include <algorithm>
#include "../../common.h"

AlphaCalculatorBase::AlphaCalculatorBase():
    mAlphas((int)CORNERS)
{
    zeroAlphas();
}

void AlphaCalculatorBase::zeroAlphas()
{
    for (auto& alpha : mAlphas)
        alpha = 0;
}

sf::Uint8 & AlphaCalculatorBase::getAlpha(size_t index)
{
    return mAlphas[index];
}

const AlphaCalculatorBase::Alphas & AlphaCalculatorBase::getAlphas() const
{
    return mAlphas;
}

void AlphaCalculatorBase::updateAlphas(const Weights & weights)
{
    zeroAlphas();
    updateAlphasAux(weights);
}
