#pragma once
#include <noise/noise.h>

namespace noise
{
namespace module
{

class ReseedableBase
{
public:
    virtual void setSeed(int seed) = 0;
    virtual Module& getModule() = 0;
    virtual const Module& getModule() const = 0;
};

} // namespace module

} // namespace noise