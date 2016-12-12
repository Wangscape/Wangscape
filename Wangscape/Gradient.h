#pragma once
#include <noise/noise.h>
#include <cmath>

// Noise module that outputs the value of x.
//
// If abs(x) > 1., then abs(output) will be too!
class GradientX : public noise::module::Module
{
public:
    GradientX() : Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return x;
    };
};

// Noise module that outputs the value of y.
//
// If abs(y) > 1., then abs(output) will be too!
class GradientY : public noise::module::Module
{
public:
    GradientY() : Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return y;
    };
};

// Noise module that outputs the value of z.
//
// If abs(z) > 1., then abs(output) will be too!
class GradientZ : public noise::module::Module
{
public:
    GradientZ() : Module(GetSourceModuleCount())
    {};
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }

    virtual double GetValue(double x, double y, double z) const
    {
        return z;
    };
};
