#pragma once
#include <noise/noise.h>

// Noise module that returns the L^p norm, raised to the power of q.
//
// That is, (|x|^p+|y|^p+|z|^p)^(q/p).
// This will have values greater than 1, even in the range [0,1]^3.
class NormLPQ : public noise::module::Module
{
public:
    NormLPQ(double p, double q=1.);
    ~NormLPQ();
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }
    virtual double GetValue(double x, double y, double z) const;
    void setPQ(double p, double q);
    void setQ(double q);
protected:
    double mP;
    double mQP;
};

