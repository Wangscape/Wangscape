#include "CornerCombinerBase.h"
#include <cmath>


namespace noise
{
namespace module
{

double CornerCombinerBase::GetPower() const
{
    return mPower;
}
void CornerCombinerBase::SetPower(double power)
{
    mPower = power;
}
CornerCombinerBase::CornerCombinerBase():
    Module(GetSourceModuleCount()),
    mPower(DEFAULT_CORNER_COMBINER_POWER)
{
}

double CornerCombinerBase::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    return (ax - ay) / pow((ax + ay + az), mPower);
}


} // namespace module
} // namespace noise

