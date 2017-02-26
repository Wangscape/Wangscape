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
    virtual ~ModuleGroupContainer() = default;
    void addSpecificModuleGroup(T key, std::string filename);
    void tryAddDefaultModuleGroup(T key, boost::optional<std::string> filename);
    std::string moduleGroupDescription;
    ModuleGroup& at(const T& key);
private:
    typedef std::map<T, std::shared_ptr<ModuleGroup>> ModuleGroups;
    ModuleGroups mModuleGroups;
};

std::shared_ptr<ModuleGroup> loadModuleGroup(std::string filename);

}
