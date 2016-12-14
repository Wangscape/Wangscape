#pragma once
#include <memory>
#include <utility>
#include <functional>
#include <noise/noise.h>

typedef noise::module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;

typedef std::pair<ModulePtr, SetSeedFn> Reseedable;

template<typename T>
SetSeedFn getSetSeed(std::shared_ptr<T> module_ptr)
{
    // TODO return module_ptr->SetSeed if that function exists
    return [](int seed) {};
};

template<typename T>
Reseedable makeReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, getSetSeed<T>(module_ptr) };
};

template<typename T>
Reseedable makeNonReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, [](int seed) {} };
};

