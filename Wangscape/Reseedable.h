#pragma once
#include <memory>
#include <utility>
#include <functional>
#include <noise/noise.h>

typedef noise::module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;
typedef std::pair<ModulePtr, SetSeedFn> Reseedable;

void dontSetSeed(int seed) {};

template<typename T>
SetSeedFn trySetSeed(std::shared_ptr<T> module_ptr)
{
    // TODO enable this specialisation only if T::SetSeed is a void(int),
    // otherwise default to the other.
    return module_ptr.get().SetSeed;
};

template<typename T>
SetSeedFn trySetSeed(std::shared_ptr<T> module_ptr)
{
    return dontSetSeed;
};

template<typename T>
Reseedable makeManualReseedable(std::shared_ptr<T> module_ptr, SetSeedFn set_seed)
{
    return{ (ModulePtr)module_ptr, set_seed };
};

template<typename T>
Reseedable makeReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, trySetSeed<T>(module_ptr) };
};

template<typename T>
Reseedable makeNonReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, dontSetSeed };
};