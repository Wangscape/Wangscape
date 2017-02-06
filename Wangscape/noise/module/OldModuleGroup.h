#pragma once
#include <noise/noise.h>
#include <string>
#include <map>
#include <memory>
#include "ReseedablePtr.h"

namespace noise
{
namespace module
{
// A helper class to store related noise modules in one place.
//
// Each component module is identified with a std::string.
// The module identified by DEFAULT_MODULE_GROUP_OUT ("output") is
// used in calls to GetValue(x,y,z).
// Component modules are stored in std::shared_ptrs,
// so they may be reused in other OldModuleGroups.
// Note that libnoise's internal pointers to source modules
// are all raw pointers, which do not have ownership,
// cannot be used to save a ModulePtr from deletion,
// and must never be used to delete a module stored
// in a ModulePtr.
// A module in a OldModuleGroup may have a source module
// which is not managed by the OldModuleGroup,
// but the OldModuleGroup will not be responsible
// for its deletion, and will be vulnerable to crashes
// if the unmanaged source module is deleted.
// This module currently has no guards against
// cyclic references between modules.
class OldModuleGroup : public Module
{
public:
    typedef std::string ModuleID;
    typedef std::map<ModuleID, ReseedablePtr> ModuleContainer;

    OldModuleGroup& insert(ModuleID name, ReseedablePtr module);
    const ReseedablePtr& at(ModuleID name) const;
    ModuleContainer::const_iterator cend() const;
    ModuleContainer::const_iterator cbegin() const;
    void SetOutputID(const ModuleID& output_id);
    const ModuleID& GetOutputID() const;

    OldModuleGroup();
    virtual ~OldModuleGroup() = default;
    virtual int GetSourceModuleCount() const;
    virtual double GetValue(double x, double y, double z) const;
    void SetSeed(int seed);
private:
    ModuleID mOutputID;
    ModuleContainer mModules;

};

const static OldModuleGroup::ModuleID DEFAULT_MODULE_GROUP_OUT = "output";


} // namespace module
} // namespace noise
