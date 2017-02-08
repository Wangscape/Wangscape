#include "EncodedModuleGroup.h"
#include "module/Wrapper.h"
#include "module/Gradient.h"
#include "module/CornerCombinerBase.h"
#include "module/Exp.h"
#include "module/Pow.h"
#include "module/NormLPQ.h"
#include "module/Forward.h"

namespace noise
{
EncodedModuleGroup::EncodedModuleGroup()
{
    moduleGroup = std::make_shared<ModuleGroup>();
}
void EncodedModuleGroup::decode()
{
    std::map<ModuleGroup::ModuleID, module::ModuleWithSources> intermediate;
    for (const auto& it : encodedModules)
    {
        std::string module_type = extractValue<std::string>(it.second, "type");
        ModuleDecodeFn decoder = mModuleDecodeTable.at(module_type);
        intermediate.insert({it.first, decoder(it.second)});
        if (module_type == "QuadrantSelector")
            moduleGroup->quadrantSelectors.push_back(it.first);
    }
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
        moduleGroup->modules.insert({it.first, it.second.module});
    }
}

EncodedModuleGroup::ModuleDecodeTable EncodedModuleGroup::mModuleDecodeTable{
    {"Abs", &EncodedModuleGroup::decodeModule<module::Abs>},
    {"Add", &EncodedModuleGroup::decodeModule<module::Add>},
    {"Billow", &EncodedModuleGroup::decodeModule<module::Billow>},
    {"Blend", &EncodedModuleGroup::decodeModule<module::Blend>},
    {"Cache", &EncodedModuleGroup::decodeModule<module::Cache>},
    {"Checkerboard", &EncodedModuleGroup::decodeModule<module::Checkerboard>},
    {"Clamp", &EncodedModuleGroup::decodeModule<module::Clamp>},
    {"Const", &EncodedModuleGroup::decodeModule<module::Const>},
    {"CornerCombinerBase", &EncodedModuleGroup::decodeModule<module::CornerCombinerBase>},
    {"Curve", &EncodedModuleGroup::decodeModule<module::Curve>},
    {"Cylinders", &EncodedModuleGroup::decodeModule<module::Cylinders>},
    {"Displace", &EncodedModuleGroup::decodeModule<module::Displace>},
    {"Exp", &EncodedModuleGroup::decodeModule<module::Exp>},
    {"Exponent", &EncodedModuleGroup::decodeModule<module::Exponent>},
    {"Forward", &EncodedModuleGroup::decodeModule<module::Forward>},
    {"GradientX", &EncodedModuleGroup::decodeModule<module::GradientX>},
    {"GradientY", &EncodedModuleGroup::decodeModule<module::GradientY>},
    {"GradientZ", &EncodedModuleGroup::decodeModule<module::GradientZ>},
    {"Invert", &EncodedModuleGroup::decodeModule<module::Invert>},
    {"Max", &EncodedModuleGroup::decodeModule<module::Max>},
    {"Min", &EncodedModuleGroup::decodeModule<module::Min>},
    {"Multiply", &EncodedModuleGroup::decodeModule<module::Multiply>},
    {"NormLPQ", &EncodedModuleGroup::decodeModule<module::NormLPQ>},
    {"Perlin", &EncodedModuleGroup::decodeModule<module::Perlin>},
    {"Pow", &EncodedModuleGroup::decodeModule<module::Pow>},
    {"Power", &EncodedModuleGroup::decodeModule<module::Power>},
    {"QuadrantSelector", &EncodedModuleGroup::decodeModule<module::QuadrantSelector>},
    {"RidgedMulti", &EncodedModuleGroup::decodeModule<module::RidgedMulti>},
    {"RotatePoint", &EncodedModuleGroup::decodeModule<module::RotatePoint>},
    {"ScaleBias", &EncodedModuleGroup::decodeModule<module::ScaleBias>},
    {"ScalePoint", &EncodedModuleGroup::decodeModule<module::ScalePoint>},
    {"Select", &EncodedModuleGroup::decodeModule<module::Select>},
    {"Spheres", &EncodedModuleGroup::decodeModule<module::Spheres>},
    {"Terrace", &EncodedModuleGroup::decodeModule<module::Terrace>},
    {"TranslatePoint", &EncodedModuleGroup::decodeModule<module::TranslatePoint>},
    {"Turbulence", &EncodedModuleGroup::decodeModule<module::Turbulence>},
    {"Voronoi", &EncodedModuleGroup::decodeModule<module::Voronoi>}
};

} // namespace noise
