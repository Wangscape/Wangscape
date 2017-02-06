#include "OldModuleGroup.h"

namespace noise
{
namespace module
{

OldModuleGroup& OldModuleGroup::insert(ModuleID name, ReseedablePtr module)
{
    mModules.insert({ name, module });
    return *this;
}

const ReseedablePtr & OldModuleGroup::at(ModuleID name) const
{
    return mModules.at(name);
}

OldModuleGroup::ModuleContainer::const_iterator OldModuleGroup::cend() const
{
    return mModules.cend();
}

OldModuleGroup::ModuleContainer::const_iterator OldModuleGroup::cbegin() const
{
    return mModules.cbegin();
}

void OldModuleGroup::SetOutputID(const ModuleID & output_id)
{
    mOutputID = output_id;
}

const OldModuleGroup::ModuleID & OldModuleGroup::GetOutputID() const
{
    return mOutputID;
}

OldModuleGroup::OldModuleGroup() :
    Module(GetSourceModuleCount()),
    mOutputID(DEFAULT_MODULE_GROUP_OUT)
{

};

int OldModuleGroup::GetSourceModuleCount() const
{
    return 0;
}

double OldModuleGroup::GetValue(double x, double y, double z) const
{
    return mModules.at(mOutputID)->getValue(x, y, z);
}

void OldModuleGroup::SetSeed(int seed)
{
    for (auto it : mModules)
    {
        // Use a different seed for each submodule
        int hash = (int)std::hash<ModuleID>{}(it.first);
        it.second->setSeed(seed^hash);
    }
};

//const OldModuleGroup::ModuleID DEFAULT_MODULE_GROUP_OUT("output");

} // namespace module
} // namespace noise
