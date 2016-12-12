#include "CornerCombinerBase.h"
#include <cmath>



CornerCombinerBase::CornerCombinerBase(double power):
    noise::module::Module(GetSourceModuleCount()),
    power(power)
{
}

double CornerCombinerBase::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    return (ax - ay) / pow((ax + ay + az), power);
}

