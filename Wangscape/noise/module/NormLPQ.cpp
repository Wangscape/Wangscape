#include "NormLPQ.h"
#include <cmath>


namespace noise
{
namespace module
{

NormLPQ::NormLPQ():
    Module(GetSourceModuleCount())
{
    SetPQ(DEFAULT_NORM_LP_Q_P, DEFAULT_NORM_LP_Q_Q);
}

double NormLPQ::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    double dp = pow(ax, mP) + pow(ay, mP) + pow(az, mP);
    return pow(dp, mQP);
}

void NormLPQ::SetPQ(double p, double q)
{
    mP = p;
    mQ = q;
    updateQP();
}

void NormLPQ::SetQ(double q)
{
    mQ = q;
    updateQP();
}

void NormLPQ::SetP(double p)
{
    mP = p;
    updateQP();
}

double NormLPQ::GetP() const
{
    return mP;
}

double NormLPQ::GetQ() const
{
    return mQ;
}

void NormLPQ::updateQP()
{
    mQP = mQ / mP;
}

} // namespace module
} // namespace noise
