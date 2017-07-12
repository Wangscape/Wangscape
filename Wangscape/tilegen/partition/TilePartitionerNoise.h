#pragma once
#include "TilePartitionerBase.h"
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "noise/module/ModulePtr.h"
#include "Options.h"
#include "noise/ModuleManager.h"
#include "noise/RasterValues.h"
#include <boost/optional.hpp>
#include "tilegen/DebugTilesetID.h"

namespace tilegen
{
namespace partition
{

class TilePartitionerNoise : public TilePartitionerBase
{
public:
    explicit TilePartitionerNoise(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    noise::module::ModulePtr makeCornerModule(const Corners & corners, bool left, bool top);
    void noiseToAlpha(std::vector<noise::RasterValues<double>>& noise_values,
                      std::vector<sf::Image>& outputs,
                      sf::Vector2u resolution) const;
private:
    noise::ModuleManager mNoiseModuleManager;
    bool mDebugOutput;
    void writeDebugGroup(const noise::ModuleGroup& module_group, tilegen::ModuleGroupRole module_group_role, bool top, bool left);
};

} // namespace partition
} // namespace tilegen
