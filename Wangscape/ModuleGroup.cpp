#include "ModuleGroup.h"

ModuleGroup::ModuleGroup() :
    Module(GetSourceModuleCount())
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
    return modules.at(OUTPUT_MODULE).get()->GetValue(x, y, z);
};

const std::string ModuleGroup::OUTPUT_MODULE("output");