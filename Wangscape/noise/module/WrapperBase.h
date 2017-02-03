#pragma once

#include <noise/noise.h>
#include "SourceModuleSlot.h"

namespace noise
{
namespace module
{

class WrapperBase
{
public:
    virtual void setSeed(int seed) = 0;
    virtual Module& getModule() = 0;
    virtual const Module& getModule() const = 0;
    void setSourceModule(int index, const Module& source_module);
    virtual void setControlModule(const Module& source_module) = 0;
    virtual void setDisplaceModule(int index, const Module& source_module) = 0;
    double getValue(double x, double y, double z) const;
};

} // namespace module

} // namespace noise
