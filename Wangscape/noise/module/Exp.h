#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// This is similar to noise::module::Exp.
// However, no rescaling is performed,
// and no attempt is made to guard against invalid operations.
// Make sure the range of the source module
// is compatible with the base of the exponential!
// This module names its parameter "base" rather than "exponent",
// because the formula is pow(base, source_value),
// not pow(source_value, exponent).
class Exp : public Module
{
public:
    double base;
    Exp() :
        Module(GetSourceModuleCount()),
        mBase(2.)
    {};
    virtual int GetSourceModuleCount() const
    {
        return 1;
    }

    void SetBase(double base)
    {
        mBase = base;
    }
    double GetBase() const
    {
        return mBase;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return pow(mBase, GetSourceModule(0).GetValue(x,y,z));
    };
protected:
    double mBase;
};

} // namespace module
} // namespace noise
