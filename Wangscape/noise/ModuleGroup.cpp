#include "ModuleGroup.h"
#include "module/Wrapper.h"
#include "module/QuadrantSelector.h"
#include "EncodedModuleGroup.h"

#include <fstream>
#include <iostream>

namespace noise
{

void noise::ModuleGroup::load(std::string filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not open options file");
    }

    std::string str{std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()};
}

void noise::ModuleGroup::setQuadrant(bool x_positive, bool y_positive, bool z_positive)
{
    for (auto module_id : mQuadrantSelectors)
    {
        module::ModulePtr qs_base_p = mModules.at(module_id);
        auto qs_p = std::static_pointer_cast<module::Wrapper<module::QuadrantSelector>>(qs_base_p);
        qs_p->module.SetTranslate(x_positive, y_positive, z_positive);
    }
}

void noise::ModuleGroup::setSeeds(int base_seed)
{
    for (auto it : mModules)
    {
        // Use a different seed for each submodule
        int hash = (int)std::hash<ModuleID>{}(it.first);
        it.second->setSeed(base_seed^hash);
    }
}

const module::ModulePtr noise::ModuleGroup::getOutputModule() const
{
    return mModules.at(outputModule);
}

module::ModulePtr noise::ModuleGroup::getInputModule(size_t index)
{
    if (index > inputModules.size())
        throw std::out_of_range("Tried to get ModuleGroup input module with index too large");
    return mModules.at(inputModules[index]);
}

void ModuleGroup::setInputModuleSource(size_t index, module::ModulePtr source_module)
{
    module::ModulePtr input_module = getInputModule(index);
    input_module->setSourceModule(0, source_module->getModule());
}

} // namespace noise
