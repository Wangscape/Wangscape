#include "CornerCombiner.h"
#include <cmath>



CornerCombiner::CornerCombiner(double power):
    noise::module::Module(GetSourceModuleCount()),
    power(power)
{
}

double CornerCombiner::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    return (ax - ay) / pow((ax + ay + az), power);
}

