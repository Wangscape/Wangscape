#pragma once

#include <utility>
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
    std::string description() const
    {
        std::string result;
        switch (moduleGroupRole)
        {
        case Combiner:
            result = "combiner.";
            break;
        case HorizontalBorder:
            result = "border_h.";
            break;
        case VerticalBorder:
            result = "border_v.";
            break;
        case Central:
            result = "central.";
            break;
        }
        result += moduleID;
        if (top)
            result.append(".T");
        else
            result.append(".B");
        if (left)
            result.append(".L");
        else
            result.append(".R");
        return result;
    }
    bool operator<(const DebugTilesetID& other) const
    {
        return std::tie(moduleGroupRole, moduleID, top, left) <
            std::tie(other.moduleGroupRole, other.moduleID, other.top, other.left);
    }
};

} // namespace tilegen
