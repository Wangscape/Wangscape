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
Reseedable makeReseedable(std::shared_ptr<T> module_ptr)
{
    // TODO make set_seed equal to module_ptr->SetSeed if that function exists
    SetSeedFn set_seed = []() {};
    return{ (ModulePtr)module_ptr, set_seed };
};

template<typename T>
Reseedable makeNonReseedable(std::shared_ptr<T> module_ptr)
{
    return{ (ModulePtr)module_ptr, []() {} };
};
