#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// Returns the first source module divided by the second.
class Divide : public Module
{
public:
    Divide() :
        Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 2;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return GetSourceModule(0).GetValue(x, y, z) / GetSourceModule(1).GetValue(x, y, z);
    };
};

} // namespace module
} // namespace noise
