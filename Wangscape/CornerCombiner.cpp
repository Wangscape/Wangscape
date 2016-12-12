#include "CornerCombiner.h"
#include <cmath>



CornerCombiner::CornerCombiner():
    noise::module::Module(GetSourceModuleCount())
{
}

double CornerCombiner::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    return (ax - ay) / (ax + ay + az);
}

