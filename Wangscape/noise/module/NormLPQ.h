#pragma once
#include <noise/noise.h>

namespace noise
{
namespace module
{

const static double DEFAULT_NORM_LP_Q_P = 2.;
const static double DEFAULT_NORM_LP_Q_Q = 1.;

// Noise module that returns the L^p norm, raised to the power of q.
//
// That is, (|x|^p+|y|^p+|z|^p)^(q/p).
// This will have values greater than 1, even in the range [0,1]^3.
class NormLPQ : public Module
{
public:
    NormLPQ();
    virtual ~NormLPQ() = default;
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }
    virtual double GetValue(double x, double y, double z) const;
    void SetPQ(double p, double q);
    void SetQ(double q);
    void SetP(double p);
    double GetP() const;
    double GetQ() const;
private:
    void updateQP();
    double mP;
    double mQ;
    double mQP;
};

} // namespace module
} // namespace noise
