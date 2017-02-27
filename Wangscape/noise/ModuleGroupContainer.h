#pragma once

#include <map>
#include <memory>

#include <boost/optional.hpp>

namespace noise
{

class ModuleGroup;

template <typename T>
class ModuleGroupContainer
{
public:
    explicit ModuleGroupContainer(std::string module_group_description_);
    virtual ~ModuleGroupContainer() = default;
    void addSpecificModuleGroup(T key, std::string filename);
    void tryAddDefaultModuleGroup(T key, boost::optional<std::string> filename);
    ModuleGroup& at(const T& key);
private:
    typedef std::map<T, std::shared_ptr<ModuleGroup>> ModuleGroups;
    ModuleGroups mModuleGroups;
    std::string mModuleGroupDescription;
};

std::shared_ptr<ModuleGroup> loadModuleGroup(std::string filename);

}
