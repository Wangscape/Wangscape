#pragma once
#include <noise/noise.h>
#include "Reseedable.h"
#include "module/ModuleGroup.h"

namespace noise
{

void dontSetSeed(int seed);

// http://stackoverflow.com/a/9531274
// Fails in VS2015
//template <typename T>
//constexpr auto is_reseedable(T& t) -> decltype(t.SetSeed(0), bool())
//{
//    return true;
//}
//constexpr bool is_reseedable(...) { return false; }

//template<typename T, bool B>
//struct Reseeder {
//    static SetSeedFn makeSetSeedFn(T& t) { return t.SetSeed; }
//};
//
//template<typename T>
//struct Reseeder<T, false> {
//    static SetSeedFn makeSetSeedFn(T& t) { return dontSetSeed; }
//};

template<typename T>
SetSeedFn trySetSeed(T* module_ptr)
{
    return dontSetSeed;
}

template<typename T>
SetSeedFn doSetSeed(T* module_ptr)
{
    return std::bind(&T::SetSeed, module_ptr, std::placeholders::_1);
}

template<typename T>
Reseedable makeManualReseedable(std::shared_ptr<T> module_ptr, SetSeedFn set_seed)
{
    return{ (ModulePtr)module_ptr, set_seed };
};

template<typename T>
Reseedable makeReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, trySetSeed<T>(module_ptr.get()) };
};

template<typename T>
Reseedable makeNonReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, dontSetSeed };
};

// This list of allowed modules is the worst thing!
// Don't let it exist for long without replacing it
// with a SFINAE template that detects if
// T::SetSeed is a void(int) function.
// VS2015 doesn't seem to support the necessary
// features for that kind of template yet. VS2017?

template<> SetSeedFn trySetSeed<module::ModuleGroup>(module::ModuleGroup* module_ptr);

template<> SetSeedFn trySetSeed<module::Billow>(module::Billow* module_ptr);
template<> SetSeedFn trySetSeed<module::Perlin>(module::Perlin* module_ptr);
template<> SetSeedFn trySetSeed<module::RidgedMulti>(module::RidgedMulti* module_ptr);
template<> SetSeedFn trySetSeed<module::Turbulence>(module::Turbulence* module_ptr);
template<> SetSeedFn trySetSeed<module::Voronoi>(module::Voronoi* module_ptr);

} // namespace noise