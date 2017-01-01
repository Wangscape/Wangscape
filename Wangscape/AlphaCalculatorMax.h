#pragma once
#include "AlphaCalculatorBase.h"
class AlphaCalculatorMax : public AlphaCalculatorBase
{
protected:
    virtual void updateAlphasAux(const Weights& weights);
};

