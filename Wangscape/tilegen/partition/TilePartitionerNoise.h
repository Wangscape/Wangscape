#pragma once
#include "TilePartitionerBase.h"
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "noise/ModuleManager.h"
#include "noise/RasterValues.h"

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
                      size_t resolution) const;
private:
    noise::ModuleManager mNoiseModuleManager;
};

} // namespace partition
} // namespace tilegen
