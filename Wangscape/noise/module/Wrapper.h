#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include "WrapperBase.h"

namespace noise
{
namespace module
{

template<typename M>
class Wrapper : public WrapperBase
{
public:
    Wrapper();
    std::shared_ptr<M> module;

    virtual void setSeed(int seed);
    virtual Module& getModule();
    virtual const Module& getModule() const;
    virtual void setControlModule(const Module& source_module);
    virtual void setDisplaceModule(int index, const Module& source_module);
};

template<typename M>
inline Wrapper<M>::Wrapper() :
    module(std::make_shared<M>())
{
}

template<typename M> void Wrapper<M>::setSeed(int seed)
{ }

template<typename M>
inline Module & Wrapper<M>::getModule()
{
    return *module;
}

template<typename M>
inline const Module & Wrapper<M>::getModule() const
{
    return *module;
}

template<typename M>
void Wrapper<M>::setControlModule(const Module & source_module)
{
    throw std::runtime_error("Tried to set ControlModule of incompatible Module");
}

template<typename M>
void Wrapper<M>::setDisplaceModule(int index, const Module & source_module)
{
    throw std::runtime_error("Tried to set DisplaceModule of incompatible Module");
}

template<> void Wrapper<Billow>::setSeed(int seed);
template<> void Wrapper<Perlin>::setSeed(int seed);
template<> void Wrapper<RidgedMulti>::setSeed(int seed);
template<> void Wrapper<Turbulence>::setSeed(int seed);
template<> void Wrapper<Voronoi>::setSeed(int seed);

template<> void Wrapper<Blend>::setControlModule(const Module& source_module);
template<> void Wrapper<Select>::setControlModule(const Module& source_module);

template<> void Wrapper<Displace>::setDisplaceModule(int index, const Module& source_module);

} // namespace noise
} // namespace module
