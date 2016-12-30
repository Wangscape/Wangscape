#pragma once

#include "metaoutput/TileLocation.h"

#include <unordered_map>

namespace metaoutput
{

using TileGroups = std::unordered_map<std::string, std::vector<TileLocation>>;

}

