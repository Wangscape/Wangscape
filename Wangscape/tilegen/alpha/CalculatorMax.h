#pragma once
#include "CalculatorBase.h"

namespace tilegen
{
namespace alpha
{

class CalculatorMax : public CalculatorBase
{
protected:
    virtual void updateAlphasAux(const Weights& weights);
};

} // namespace alpha
} // namespace tilegen
