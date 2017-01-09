#pragma once
#include <noise/noise.h>
#include <memory>
#include "ModuleGroup.h"

namespace noise
{
namespace module
{

class ReseedableBase
{
public:
    virtual void SetSeed(int seed) = 0;
    virtual Module& getModule();
    virtual const Module& getModule() const;
};

template<typename M>
class ReseedableT : public ReseedableBase
{
public:
    virtual void SetSeed(int seed);
    virtual Module& getModule();
    virtual const Module& getModule() const;

    M module;
};

template<typename M> void ReseedableT<M>::SetSeed(int seed)
{ }

template<typename M>
inline Module & ReseedableT<M>::getModule()
{
    return module;
}

template<typename M>
inline const Module & ReseedableT<M>::getModule() const
{
    return module;
}

template<> void ReseedableT<ModuleGroup>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void ReseedableT<Billow>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void ReseedableT<Perlin>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void ReseedableT<RidgedMulti>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void ReseedableT<Turbulence>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void ReseedableT<Voronoi>::SetSeed(int seed)
{
    module.SetSeed(seed);
}

} // namespace module

} // namespace noise