#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// Returns 1 divided by the source module.
class Reciprocal : public Module
{
public:
    Reciprocal() :
        Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 1;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return 1.0/GetSourceModule(0).GetValue(x, y, z);
    };
};

} // namespace module
} // namespace noise
