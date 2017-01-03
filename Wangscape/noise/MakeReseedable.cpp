#include "MakeReseedable.h"

namespace noise
{

void dontSetSeed(int seed) {}

template<> SetSeedFn trySetSeed<module::ModuleGroup>(module::ModuleGroup* module_ptr) { return doSetSeed(module_ptr); }

template<> SetSeedFn trySetSeed<module::Billow>(module::Billow* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<module::Perlin>(module::Perlin* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<module::RidgedMulti>(module::RidgedMulti* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<module::Turbulence>(module::Turbulence* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<module::Voronoi>(module::Voronoi* module_ptr) { return doSetSeed(module_ptr); }

} // namespace noise