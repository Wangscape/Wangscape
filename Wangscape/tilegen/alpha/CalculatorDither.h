#pragma once

#include <random>
#include "CalculatorTopTwo.h"

namespace tilegen
{
namespace alpha
{

class CalculatorDither : public CalculatorTopTwo
{
public:
    CalculatorDither();
protected:
    virtual void updateAlphasAux(const Weights& weights) override;
private:
    std::mt19937 mRNG;
    std::uniform_real_distribution<double> mUniformRealDistribution;
};

} // namespace alpha
} // namespace tilegen
