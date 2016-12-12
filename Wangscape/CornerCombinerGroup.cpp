#include "CornerCombinerGroup.h"

CornerCombinerGroup::CornerCombinerGroup(double power):
    mCornerCombiner(power)
{
    mClamp.SetBounds(0., 1.);
    mScaleBias.SetBias(0.5);
    mScaleBias.SetScale(0.5);
    mClamp.SetSourceModule(0,mScaleBias);
    mScaleBias.SetSourceModule(0, mCornerCombiner);
}

const noise::module::Module & CornerCombinerGroup::getOutput() const
{
    return mClamp;
}
