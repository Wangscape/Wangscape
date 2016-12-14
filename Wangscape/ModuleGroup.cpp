#include "ModuleGroup.h"

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
    return modules.at(output_id).first.get()->GetValue(x, y, z);
}

void ModuleGroup::SetSeed(int seed)
{
    for (auto it : modules)
    {
        // Use a different seed for each submodule
        int hash = (int)std::hash<ModuleID>{}(it.first);
        it.second.second(seed^hash);
    }
};

const std::string ModuleGroup::DEFAULT_OUT("output");