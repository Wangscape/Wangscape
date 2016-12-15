#include "ModuleGroup.h"

void ModuleGroup::insert(ModuleID name, Reseedable module)
{
    mModules.insert({ name, module });
}

const Reseedable & ModuleGroup::at(ModuleID name) const
{
    return mModules.at(name);
}

ModuleGroup::ModuleContainer::const_iterator ModuleGroup::cend() const
{
    return mModules.cend();
}

ModuleGroup::ModuleContainer::const_iterator ModuleGroup::cbegin() const
{
    return mModules.cbegin();
}

ModuleGroup::ModuleGroup(ModuleID output_id) :
    Module(GetSourceModuleCount()),
    output_id(output_id)
{

};

int ModuleGroup::GetSourceModuleCount() const
{
    return 0;
}

ModuleGroup::~ModuleGroup()
{

};

double ModuleGroup::GetValue(double x, double y, double z) const
{
    return mModules.at(output_id).module.get()->GetValue(x, y, z);
}

void ModuleGroup::SetSeed(int seed)
{
    for (auto it : mModules)
    {
        // Use a different seed for each submodule
        int hash = (int)std::hash<ModuleID>{}(it.first);
        it.second.setSeed(seed^hash);
    }
};

const std::string ModuleGroup::DEFAULT_OUT("output");