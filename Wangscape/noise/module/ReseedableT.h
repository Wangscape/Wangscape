#pragma once
#include <noise/noise.h>
#include "ModuleGroup.h"

namespace noise
{
namespace module
{

class ReseedableBase : public virtual Module
{
public:
    virtual void SetSeed(int seed) = 0;
};

template<typename M>
class ReseedableT :
    public virtual ReseedableBase,
    public virtual M
{
public:
    ReseedableT() :
        M::Module(GetSourceModuleCount()),
        M()
    { }
    virtual int GetSourceModuleCount() const
    {
        return M::GetSourceModuleCount();
    }
    virtual double GetValue(double x, double y, double z) const
    {
        return M::GetValue(x, y, z);
    }
    virtual void SetSeed(int seed);
};

template<typename M> void ReseedableT<M>::SetSeed(int seed)
{ }

template<> void ReseedableT<ModuleGroup>::SetSeed(int seed)
{
    ModuleGroup::SetSeed(seed);
}

template<> void ReseedableT<Billow>::SetSeed(int seed)
{
    Billow::SetSeed(seed);
}

template<> void ReseedableT<Perlin>::SetSeed(int seed)
{
    Perlin::SetSeed(seed);
}

template<> void ReseedableT<RidgedMulti>::SetSeed(int seed)
{
    RidgedMulti::SetSeed(seed);
}

template<> void ReseedableT<Turbulence>::SetSeed(int seed)
{
    Turbulence::SetSeed(seed);
}

template<> void ReseedableT<Voronoi>::SetSeed(int seed)
{
    Voronoi::SetSeed(seed);
}

typedef std::shared_ptr<ReseedableBase> ReseedablePtr;

} // namespace module

} // namespace noise