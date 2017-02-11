#pragma once

#include <utility>
#include <vector>

#include "CalculatorBase.h"


namespace tilegen
{
namespace alpha
{


class CalculatorTopTwo :
    public tilegen::alpha::CalculatorBase
{
public:
    double power = 1.;
protected:
    virtual void updateAlphasAux(const Weights& weights);
private:
    typedef std::pair<double, size_t> IndexedWeight;
    std::vector<IndexedWeight> mIndexedWeights;
    void initialiseIndexedWeights(const Weights& weights);
};

} // namespace alpha
} // namespace tilegen
