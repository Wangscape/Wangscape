#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// Default base for the noise::module::Logarithm noise module.
const static double DEFAULT_LOGARITHM_BASE = 2;

// Returns a logarithm of the source module.
// The base of the logarithm is specified with the Base parameter,
// which by default is 2.
class Logarithm : public Module
{
public:
    Logarithm() :
        Module(GetSourceModuleCount()),
        mBase(DEFAULT_LOGARITHM_BASE)
    {};
    virtual int GetSourceModuleCount() const
    {
        return 1;
    }

    void SetBase(double base)
    {
        mBase = base;
        mLogBase = std::log(base);
    }
    double GetBase() const
    {
        return mBase;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return std::log(GetSourceModule(0).GetValue(x, y, z)) / mLogBase;
    };
private:
    double mBase;
    double mLogBase;
};

} // namespace module
} // namespace noise
