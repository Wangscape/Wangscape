#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// Default base for the noise::module::Exp noise module.
const static double DEFAULT_EXP_BASE = 2;

// Raises a constant value to a variable power given by a module.
// Complementary operation to noise::module::Pow.
// No attempt is made to guard against invalid operations.
// Make sure the range of the source module
// is compatible with the base of the exponential!
// This module names its parameter "base" rather than "exponent",
// because the formula is pow(base, source_value),
// not pow(source_value, exponent).
class Exp : public Module
{
public:
    Exp() :
        Module(GetSourceModuleCount()),
        mBase(DEFAULT_EXP_BASE)
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
        return std::pow(mBase, GetSourceModule(0).GetValue(x,y,z));
    };
private:
    double mBase;
};

} // namespace module
} // namespace noise
