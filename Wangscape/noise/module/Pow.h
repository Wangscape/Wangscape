#pragma once
#pragma once
#include <noise/noise.h>
#include <cmath>

namespace noise
{
namespace module
{

// Default base for the noise::module::Exp noise module.
const static double DEFAULT_POW_EXPONENT = 1.;

// Noise module that raises a source module to an exponent.
// This is similar to noise::module::Exponent.
// However, no rescaling is performed,
// and no attempt is made to guard against invalid operations.
// Make sure the range of the source module
// is compatible with the exponent!
// The formula is pow(source_value, exponent)
class Pow : public Module
{
public:
    double exponent;
    Pow() :
        Module(GetSourceModuleCount()),
        mExponent(DEFAULT_POW_EXPONENT)
    {};
    virtual int GetSourceModuleCount() const
    {
        return 1;
    }

    void SetExponent(double exponent)
    {
        mExponent = exponent;
    }
    double GetExponent() const
    {
        return mExponent;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return std::pow(GetSourceModule(0).GetValue(x, y, z), mExponent);
    };
private:
    double mExponent;
};


} // namespace module
} // namespace noise
