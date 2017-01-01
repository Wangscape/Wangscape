#pragma once
#include "AlphaCalculatorBase.h"

namespace tilegen
{
namespace alpha
{

class AlphaCalculatorMax : public AlphaCalculatorBase
{
protected:
    virtual void updateAlphasAux(const Weights& weights);
};

} // namespace alpha
} // namespace tilegen
