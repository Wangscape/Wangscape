#include "ModuleWithSources.h"

namespace noise
{
namespace module
{
ModuleWithSources::ModuleWithSources(ModulePtr module_, NoiseSources noise_sources_) :
    module(module_),
    noiseSources(noise_sources_)
{
}

void ModuleWithSources::setModuleSources(std::function<const Module&(const std::string&)> findModule)
{
    if (noiseSources.sourceModules)
    {
        auto sm = noiseSources.sourceModules.get();
        for (size_t i = 0; i < sm.size(); i++)
        {
            module->setSourceModule(i, findModule(sm[i]));
        }
    }
    if (noiseSources.controlModule)
    {
        module->setControlModule(findModule(noiseSources.controlModule.get()));
    }
    if (noiseSources.displaceModules)
    {
        auto dm = noiseSources.displaceModules.get();
        for (size_t i = 0; i < dm.size(); i++)
        {
            module->setDisplaceModule(i, findModule(dm[i]));
        }
    }
}

} // namespace noise
} // namespace module
