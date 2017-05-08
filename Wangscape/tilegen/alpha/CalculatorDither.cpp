#include "CalculatorDither.h"

namespace tilegen
{
namespace alpha
{



CalculatorDither::CalculatorDither() :
    mRNG(std::random_device()()),
    mUniformRealDistribution(0., 1.)
{
}

void CalculatorDither::updateAlphasAux(const Weights & weights)
{
    TopTwoInfo top_two_info = calculateTopTwoInfo(weights);
    if (mUniformRealDistribution(mRNG) < std::pow(top_two_info.ratio, power))
        getAlpha(top_two_info.runner_up) = 255;
    else
        getAlpha(top_two_info.winner) = 255;
}

} // namespace alpha
} // namespace tilegen
