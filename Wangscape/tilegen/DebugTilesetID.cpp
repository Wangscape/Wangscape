#include "DebugTilesetID.h"
#include <map>
#include <utility>

namespace tilegen
{

namespace
{

const static std::map<ModuleGroupRole, std::string> role_names = {
    {ModuleGroupRole::Combiner, "combiner"},
    {ModuleGroupRole::HorizontalBorder, "border_h"},
    {ModuleGroupRole::VerticalBorder, "border_v"},
    {ModuleGroupRole::Central, "central"}
};

const static std::map<std::pair<bool, bool>, std::string> corner_names = {
    {{true, true}, "TL"},
    {{true, false}, "TR"},
    {{false, true}, "BL"},
    {{false, false}, "BR"}
};

}

std::string DebugTilesetID::description() const
{
    return role_names.at(moduleGroupRole) + "." + moduleID + "." + corner_names.at({top, left});
}


bool DebugTilesetID::operator<(const DebugTilesetID& other) const
{
    return std::tie(moduleGroupRole, moduleID, top, left) <
        std::tie(other.moduleGroupRole, other.moduleID, other.top, other.left);
}

} // namespace tilegen
