#pragma once
#include "CalculatorBase.h"

namespace tilegen
{
namespace alpha
{

class CalculatorLinear : public CalculatorBase
{
protected:
    // This Calculator class requires input weights
    // to be all nonnegative,
    // and to have a sum significantly greater than 0.
    // If these conditions are not satisfied,
    // visual artefacts will be present in the output tilesets.
    virtual void updateAlphasAux(const Weights& weights) override;
};


} // namespace alpha
} // namespace tilegen
