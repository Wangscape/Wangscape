#pragma once
#include "TilePartitionerBase.h"
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "noise/module/ModulePtr.h"
#include "Options.h"
#include "noise/ModuleManager.h"
#include "noise/RasterValues.h"
#include "DebugWriter.h"
#include <boost/optional.hpp>

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
    boost::optional<DebugWriter> mDebugWriter;
    void writeDebugData(const noise::ModuleGroup& central,
                        const noise::ModuleGroup& border_h,
                        const noise::ModuleGroup& border_v,
                        const noise::ModuleGroup& combiner);
};

} // namespace partition
} // namespace tilegen
