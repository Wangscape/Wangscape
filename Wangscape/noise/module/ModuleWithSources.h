#pragma once
#include <functional>
#include "ModulePtr.h"
#include "NoiseSources.h"

namespace noise
{
namespace module
{

struct ModuleWithSources
{
    ModuleWithSources() = default;
    ModuleWithSources(ModulePtr module_, NoiseSources noise_sources_);
    ModulePtr module;
    NoiseSources noiseSources;
    void setModuleSources(std::function<const Module&(const std::string&)> findModule);
};

} // namespace noise
} // namespace module
