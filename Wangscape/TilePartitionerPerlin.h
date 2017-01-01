#pragma once
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "noise/ModuleManager.h"
#include "TilePartitionerBase.h"

#include "noise/RasterValues.h"

using Reseedable = noise::Reseedable;

class TilePartitionerPerlin : public TilePartitionerBase
{
public:
    explicit TilePartitionerPerlin(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    void noiseToAlpha(std::vector<noise::RasterValues<float>>& noise_values,
                      std::vector<sf::Image>& outputs,
                      size_t resolution);
    void makeCorner(noise::RasterValues<float> & noise_map_vector,
                    const Corners& corners,
                    bool left, bool top);
protected:
    noise::ModuleManager mNoiseModuleManager;
};
