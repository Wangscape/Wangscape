#pragma once
#include <memory>
#include "ReseedableBase.h"
#include "OldModuleGroup.h"

namespace noise
{
namespace module
{

template<typename M>
class Reseedable : public ReseedableBase
{
public:
    virtual void setSeed(int seed);
    virtual Module& getModule();
    virtual const Module& getModule() const;

    M module;
};

template<typename M> void Reseedable<M>::setSeed(int seed)
{ }

template<typename M>
inline Module & Reseedable<M>::getModule()
{
    return module;
}

template<typename M>
inline const Module & Reseedable<M>::getModule() const
{
    return module;
}

template<> void Reseedable<OldModuleGroup>::setSeed(int seed);

template<> void Reseedable<Billow>::setSeed(int seed);

template<> void Reseedable<Perlin>::setSeed(int seed);

template<> void Reseedable<RidgedMulti>::setSeed(int seed);

template<> void Reseedable<Turbulence>::setSeed(int seed);

template<> void Reseedable<Voronoi>::setSeed(int seed);

} // namespace noise
} // namespace module
