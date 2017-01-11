#include "Reseedable.h"

namespace noise
{
namespace module
{

template<> void Reseedable<ModuleGroup>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Reseedable<Billow>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Reseedable<Perlin>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Reseedable<RidgedMulti>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Reseedable<Turbulence>::setSeed(int seed)
{
    module.SetSeed(seed);
}

template<> void Reseedable<Voronoi>::setSeed(int seed)
{
    module.SetSeed(seed);
}

} // namespace noise
} // namespace module
