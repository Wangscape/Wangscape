#include "Wrapper.h"

namespace noise
{
namespace module
{

template<> void Wrapper<Billow>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Wrapper<Perlin>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Wrapper<RidgedMulti>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Wrapper<Turbulence>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Wrapper<Voronoi>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Wrapper<Displace>::setDisplaceModule(int index, const Module& source_module)
{
    switch (index)
    {
    case 0:
        module.SetXDisplaceModule(source_module);
        break;
    case 1:
        module.SetYDisplaceModule(source_module);
        break;
    case 2:
        module.SetZDisplaceModule(source_module);
        break;
    default:
        throw std::runtime_error("Tried to set displace module with index not 0, 1, or 2");
    }
}

template<> void Wrapper<Blend>::setControlModule(const Module& source_module)
{
    module.SetControlModule(source_module);
}

template<> void Wrapper<Select>::setControlModule(const Module& source_module)
{
    module.SetControlModule(source_module);
}

} // namespace noise
} // namespace module
