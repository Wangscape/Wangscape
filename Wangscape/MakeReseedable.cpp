#include "MakeReseedable.h"


void dontSetSeed(int seed) {}

template<> SetSeedFn trySetSeed<ModuleGroup>(ModuleGroup* module_ptr) { return doSetSeed(module_ptr); }

template<> SetSeedFn trySetSeed<noise::module::Billow>(noise::module::Billow* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<noise::module::Perlin>(noise::module::Perlin* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<noise::module::RidgedMulti>(noise::module::RidgedMulti* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<noise::module::Turbulence>(noise::module::Turbulence* module_ptr) { return doSetSeed(module_ptr); }
template<> SetSeedFn trySetSeed<noise::module::Voronoi>(noise::module::Voronoi* module_ptr) { return doSetSeed(module_ptr); }