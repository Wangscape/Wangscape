#include "EncodedModuleGroup.h"
#include "module/Wrapper.h"
#include "module/ModuleGroup.h"
#include "module/codecs/VoronoiCodec.h"
#include "module/codecs/PerlinCodec.h"

namespace noise
{

std::map<std::string, module::ModulePtr> noise::EncodedModuleGroup::decode() const
{
    std::map<std::string, module::ModuleWithSources> intermediate;
    for (const auto& it : encodedModules)
    {
        std::string module_type = extractValue<std::string>(it.second, "type");
        ModuleDecodeFn decoder = mModuleDecodeTable.at(module_type);
        intermediate.insert({it.first, decoder(it.second)});
    }
    std::map<std::string, module::ModulePtr> result;
    for (auto it : intermediate)
    {
        // ModuleWithSources::setModuleSources is designed to do this job as follows:
        //
        //it.second.setModuleSources([&intermediate](const std::string& module_id)
        //{
        //    return intermediate.at(module_id).module->getModule();
        //});
        //
        // but using it as above produces warnings and does not correctly set the source module addresses.
        // TODO: do this with std::transform and boost::adaptors::index.
        if (it.second.noiseSources.sourceModules)
        {
            auto sm = it.second.noiseSources.sourceModules.get();
            for (size_t i = 0; i < sm.size(); i++)
            {
                it.second.module->setSourceModule(i, intermediate.at(sm[i]).module->getModule());
            }
        }
        if (it.second.noiseSources.controlModule)
        {
            it.second.module->setControlModule(intermediate.at(it.second.noiseSources.controlModule.get()).module->getModule());
        }
        if (it.second.noiseSources.displaceModules)
        {
            auto dm = it.second.noiseSources.displaceModules.get();
            for (size_t i = 0; i < dm.size(); i++)
            {
                it.second.module->setDisplaceModule(i, intermediate.at(dm[i]).module->getModule());
            }
        }
        result.insert({it.first, it.second.module});
    }
    return result;
}

EncodedModuleGroup::ModuleDecodeTable EncodedModuleGroup::mModuleDecodeTable{
    {"Add", &EncodedModuleGroup::decodeModule<module::Add>},
    {"Perlin", &EncodedModuleGroup::decodeModule<module::Perlin>},
    {"Voronoi", &EncodedModuleGroup::decodeModule<module::Voronoi>}
};

} // namespace noise
