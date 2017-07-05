#pragma once

#include "ModuleGroupRole.h"
#include "noise/ModuleID.h"

namespace tilegen
{

struct DebugTilesetID
{
    ModuleGroupRole moduleGroupRole;
    noise::ModuleID moduleID;
    bool top;
    bool left;
    DebugTilesetID(ModuleGroupRole moduleGroupRole_,
                   noise::ModuleID moduleID_,
                   bool top_,
                   bool left_) :
        moduleGroupRole(moduleGroupRole_),
        moduleID(moduleID_),
        top(top_),
        left(left_)
    {}
    std::string description() const;
    bool operator<(const DebugTilesetID& other) const;
};

} // namespace tilegen
