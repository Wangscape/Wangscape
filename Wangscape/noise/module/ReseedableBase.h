#pragma once
#include <noise/noise.h>

namespace noise
{
namespace module
{

class ReseedableBase
{
public:
    virtual void setSeed(int seed) = 0;
    virtual Module& getModule() = 0;
    virtual const Module& getModule() const = 0;
    double getValue(double x, double y, double z) const
    {
        return getModule().GetValue(x, y, z);
    };
};

} // namespace module

} // namespace noise