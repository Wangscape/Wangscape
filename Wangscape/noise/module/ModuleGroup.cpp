#include "ModuleGroup.h"

namespace noise
{
namespace module
{

ModuleGroup& ModuleGroup::insert(ModuleID name, ReseedablePtr module)
{
    mModules.insert({ name, module });
    return *this;
}

const ReseedablePtr & ModuleGroup::at(ModuleID name) const
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

void ModuleGroup::SetOutputID(const ModuleID & output_id)
{
    mOutputID = output_id;
}

const ModuleGroup::ModuleID & ModuleGroup::GetOutputID() const
{
    return mOutputID;
}

ModuleGroup::ModuleGroup() :
    Module(GetSourceModuleCount()),
    mOutputID(DEFAULT_MODULE_GROUP_OUT)
{

};

int ModuleGroup::GetSourceModuleCount() const
{
    return 0;
}

double ModuleGroup::GetValue(double x, double y, double z) const
{
    return mModules.at(mOutputID)->getValue(x, y, z);
}

void ModuleGroup::SetSeed(int seed)
{
    for (auto it : mModules)
    {
        // Use a different seed for each submodule
        int hash = (int)std::hash<ModuleID>{}(it.first);
        it.second->setSeed(seed^hash);
    }
};

//const ModuleGroup::ModuleID DEFAULT_MODULE_GROUP_OUT("output");

} // namespace module
} // namespace noise
