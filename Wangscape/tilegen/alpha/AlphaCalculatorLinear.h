#pragma once
#include "AlphaCalculatorBase.h"

namespace tilegen
{
namespace alpha
{

class AlphaCalculatorLinear : public AlphaCalculatorBase
{
protected:
    // This AlphaCalculator class requires input weights
    // to be all nonnegative,
    // and to have a sum significantly reater than 0.
    // If these conditions are not satisfied,
    // visual artefacts will be present in the output tilesets.
    virtual void updateAlphasAux(const Weights& weights);
};


} // namespace alpha
} // namespace tilegen
