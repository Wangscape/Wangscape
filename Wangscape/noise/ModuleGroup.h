#pragma once
#include <map>
#include <string>
#include <vector>
#include "noise/module/ModulePtr.h"

namespace noise
{

class ModuleGroup
{
public:
    typedef std::string ModuleID;
    virtual ~ModuleGroup();
    
    void load(std::string filename);
    void setQuadrant(bool x_positive, bool y_positive, bool z_positive);
    void setSeeds(int base_seed);
    const module::ModulePtr getOutputModule() const;
    module::ModulePtr getInputModule(size_t index);
    void setInputModuleSource(size_t index, module::ModulePtr source_module);
private:
    std::vector<ModuleID> mQuadrantSelectors;
    std::map<ModuleID, module::ModulePtr> mModules;
    ModuleID outputModule;
    std::vector<ModuleID> inputModules;
};

} //namespace noise