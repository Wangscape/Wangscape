#pragma once
#include <noise/noise.h>

// Noise module that outputs a radial pattern.
// It is approximately equal to 1 along the x axis,
// to -1 along the y axis, and to 0.5 along the
// x+y and x-y axes. To avoid division by zero,
// z should be nonzero (but may be small).
class CornerCombiner : public noise::module::Module
{
public:
    CornerCombiner();
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }

    virtual double GetValue(double x, double y, double z) const;
};

