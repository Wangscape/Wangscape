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


class TilePartitionerPerlin : public TilePartitionerBase
{
public:
    using ReseedablePtr = noise::module::ReseedablePtr;
    explicit TilePartitionerPerlin(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    ReseedablePtr makeCornerModule(const Corners & corners, bool left, bool top);
    void noiseToAlpha(std::vector<noise::RasterValues<float>>& noise_values,
                      std::vector<sf::Image>& outputs,
                      size_t resolution) const;
private:
    noise::ModuleManager mNoiseModuleManager;
};

} // namespace partition
} // namespace tilegen
