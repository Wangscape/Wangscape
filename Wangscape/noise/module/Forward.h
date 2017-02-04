#pragma once
#include <noise/noise.h>

namespace noise
{
namespace module
{

class Forward : public Module
{
public:
    double base;
    Forward() :
        Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 1;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return GetSourceModule(0).GetValue(x, y, z);
    };
};

} // namespace module
} // namespace noise
