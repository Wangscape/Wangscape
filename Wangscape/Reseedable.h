#pragma once
#include <memory>
#include <utility>
#include <functional>
#include <noise/noise.h>

typedef noise::module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;
typedef std::pair<ModulePtr, SetSeedFn> Reseedable;
