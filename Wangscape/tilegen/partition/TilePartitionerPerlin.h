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

using Reseedable = noise::Reseedable;

class TilePartitionerPerlin : public TilePartitionerBase
{
public:
    explicit TilePartitionerPerlin(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    Reseedable makeCornerModule(const Corners & corners, bool left, bool top);
    void noiseToAlpha(std::vector<noise::RasterValues<double>>& noise_values,
                      std::vector<sf::Image>& outputs,
                      sf::Vector2u resolution) const;
private:
    noise::ModuleManager mNoiseModuleManager;
};

} // namespace partition
} // namespace tilegen
