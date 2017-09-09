#pragma once

#include <map>
#include <memory>
#include <string>
#include <random>

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
    void addSpecificModuleGroup(T key, std::string filename, std::mt19937& rng);
    void tryAddDefaultModuleGroup(T key, boost::optional<std::string> filename, std::mt19937& rng);
    ModuleGroup& at(const T& key);
private:
    typedef std::map<T, std::shared_ptr<ModuleGroup>> ModuleGroups;
    ModuleGroups mModuleGroups;
    std::string mModuleGroupDescription;
};

std::shared_ptr<ModuleGroup> loadModuleGroup(std::string filename);

}
