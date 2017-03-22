#include "ModuleGroup.h"
#include "module/Wrapper.h"
#include "module/QuadrantSelector.h"

namespace noise
{

void ModuleGroup::setQuadrant(bool x_positive, bool y_positive, bool z_positive)
{
    for (auto module_id : mQuadrantSelectors)
    {
        module::ModulePtr qs_base_p = mModules.at(module_id);
        auto qs_p = std::static_pointer_cast<module::Wrapper<module::QuadrantSelector>>(qs_base_p);
        qs_p->module->SetTranslate(!x_positive, !y_positive, !z_positive);
    }
}

void ModuleGroup::setSeeds(int base_seed)
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
    return mModules.at(mOutputModule);
}

module::ModulePtr noise::ModuleGroup::getInputModule(size_t index)
{
    if (index > mInputModules.size())
        throw std::out_of_range("Tried to get ModuleGroup input module with index too large");
    return mModules.at(mInputModules[index]);
}

void ModuleGroup::setInputModuleSource(size_t index, module::ModulePtr source_module)
{
    module::ModulePtr input_module = getInputModule(index);
    input_module->setSourceModule(0, source_module->getModule());
}

const std::map<ModuleID, module::ModulePtr>& ModuleGroup::getModules() const
{
    return mModules;
}

std::shared_ptr<ModuleGroup> ModuleGroup::makeConstModuleGroup(double const_value)
{
    auto result = std::make_shared<ModuleGroup>();
    auto module = std::make_shared<module::Wrapper<module::Const>>();
    module->module->SetConstValue(const_value);
    result->mModules["OUTPUT"] = module;
    result->mOutputModule = "OUTPUT";
    return result;
}

} // namespace noise
