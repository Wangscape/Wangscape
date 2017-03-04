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
    struct TopTwoInfo
    {
        size_t winner;
        size_t runner_up;
        double ratio;
    };
    TopTwoInfo calculateTopTwoInfo(const Weights& weights);
    virtual void updateAlphasAux(const Weights& weights) override;
private:
    typedef std::pair<double, size_t> IndexedWeight;
    std::vector<IndexedWeight> mIndexedWeights;
    void initialiseIndexedWeights(const Weights& weights);
};

} // namespace alpha
} // namespace tilegen
