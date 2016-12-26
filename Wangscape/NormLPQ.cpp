#include "NormLPQ.h"
#include <cmath>



NormLPQ::NormLPQ(double p, double q):
    Module(GetSourceModuleCount())
{
    setPQ(p, q);
}

double NormLPQ::GetValue(double x, double y, double z) const
{
    double ax = std::abs(x);
    double ay = std::abs(y);
    double az = std::abs(z);
    double dp = pow(ax, mP) + pow(ay, mP) + pow(az, mP);
    return pow(dp, mQP);
}

void NormLPQ::setPQ(double p, double q)
{
    mP = p;
    setQ(q);
}

void NormLPQ::setQ(double q)
{
    mQP = q / mP;
}
