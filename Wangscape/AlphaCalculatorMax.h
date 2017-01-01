#pragma once
#include "AlphaCalculatorBase.h"
class AlphaCalculatorMax : public AlphaCalculatorBase
{
protected:
    virtual void calculateAlphasAux(const Weights& weights, Alphas& alphas) const;
};

