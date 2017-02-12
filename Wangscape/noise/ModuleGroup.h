#pragma once
#include <map>
#include <string>
#include <vector>
#include "noise/module/ModulePtr.h"

namespace spotify
{
namespace json
{
template<typename T> struct default_codec_t;
}
}

namespace noise
{
class EncodedModuleGroup;

class ModuleGroup
{
public:
    virtual ~ModuleGroup() = default;
    typedef std::string ModuleID;
    
    void setQuadrant(bool x_positive, bool y_positive, bool z_positive);
    void setSeeds(int base_seed);
    const module::ModulePtr getOutputModule() const;
    void setInputModuleSource(size_t index, module::ModulePtr source_module);
    const std::map<ModuleID, module::ModulePtr>& getModules() const;
private:
    friend class EncodedModuleGroup;
    //template<> 
    friend struct spotify::json::default_codec_t<EncodedModuleGroup>;

    module::ModulePtr getInputModule(size_t index);
    std::vector<ModuleID> mQuadrantSelectors;
    std::map<ModuleID, module::ModulePtr> mModules;
    ModuleID mOutputModule;
    std::vector<ModuleID> mInputModules;
};

} //namespace noise