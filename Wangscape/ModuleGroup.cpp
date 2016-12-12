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
    return modules[0].get()->GetValue(x, y, z);
};