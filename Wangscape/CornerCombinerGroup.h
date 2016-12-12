#pragma once

#include <noise/noise.h>
#include "CornerCombiner.h"


class CornerCombinerGroup
{
public:
    CornerCombinerGroup(double power = 1);
    const noise::module::Module& getOutput() const;
protected:
    CornerCombiner mCornerCombiner;
    noise::module::Clamp mClamp;
    noise::module::ScaleBias mScaleBias;
};