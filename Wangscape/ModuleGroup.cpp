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
    return modules.at(output_id).get()->GetValue(x, y, z);
};

const std::string ModuleGroup::DEFAULT_OUT("output");