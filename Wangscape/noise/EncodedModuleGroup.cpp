#include "EncodedModuleGroup.h"
#include "module/WangscapeModules.h"
#include "module/Wrapper.h"
#include "ModuleGroup.h"

namespace noise
{
EncodedModuleGroup::EncodedModuleGroup()
{
    moduleGroup = std::make_shared<ModuleGroup>();
}
void EncodedModuleGroup::decode()
{
    std::map<ModuleID, module::ModuleWithSources> intermediate;
    for (const auto& it : encodedModules)
    {
        std::string module_type = extractValue<std::string>(it.second, "type");
        ModuleDecodeFn decoder = moduleDecodeTable.at(module_type);
        intermediate.insert({it.first, decoder(it.second)});
        if (module_type == "QuadrantSelector")
            moduleGroup->mQuadrantSelectors.push_back(it.first);
    }
    for (auto it : intermediate)
    {
        it.second.setModuleSources([&intermediate](const std::string& module_id)
                                   -> const noise::module::Module&
        {
            return intermediate.at(module_id).module->getModule();
        });
        moduleGroup->mModules.insert({it.first, it.second.module});
    }
    for (auto input_module_id : moduleGroup->mInputModules)
    {
        if (moduleGroup->mModules.at(input_module_id)->getModule().GetSourceModuleCount() < 1)
        {
            throw std::runtime_error("Tried to set ModuleGroup input module to a type which has no source modules");
        }
    }
}

namespace
{

ModuleDecodeTable moduleDecodeTable = {
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
}
} // namespace noise
