#pragma once
#include <noise/noise.h>
namespace noise
{
namespace module
{
// Default power for the noise::module::CornerCombinerBase module.
const static double DEFAULT_CORNER_COMBINER_POWER = 1.;

// Noise module that outputs a radial pattern.
//
// When power is 1.0, it is approximately equal
// to 1 along the x axis, to -1 along the y axis,
// and to 0.5 along the x + y and x - y axes.
// To avoid division by zero, z should be nonzero
// (but may be small).
//
// When power is not 1.0, the global output will
// not be bounded in [-1., 1.].
//
// When power is less than 1.0, the magnitude of
// the output will be less than 1.0 along the axes
// when x, y are in [-1., 1.].
//
// When power is greater than 1.0, the magnitude of
// the output will be greater than 1.0 along the axes
// when x, y are in [-1., 1.], and the output should
// be clamped.
class CornerCombinerBase : public Module
{
public:
    CornerCombinerBase();
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }
    double GetPower() const;
    void SetPower(double power);

    virtual double GetValue(double x, double y, double z) const;
private:
    double mPower;
};

} // namespace module
} // namespace noise
