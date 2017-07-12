#pragma once

#include "ModuleGroupRole.h"
#include "noise/ModuleID.h"

namespace tilegen
{

class DebugTilesetID
{
public:
    DebugTilesetID(ModuleGroupRole moduleGroupRole_,
                   noise::ModuleID moduleID_,
                   bool top_,
                   bool left_) :
        mModuleGroupRole(moduleGroupRole_),
        mModuleID(moduleID_),
        mTop(top_),
        mLeft(left_)
    {}
    std::string description() const;
    bool operator<(const DebugTilesetID& other) const;
private:
    ModuleGroupRole mModuleGroupRole;
    noise::ModuleID mModuleID;
    bool mTop;
    bool mLeft;
};

} // namespace tilegen
