#pragma once
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "noise/NoiseModuleManager.h"
#include "TilePartitionerBase.h"

#include "noise/NoiseMap.h"

using Reseedable = noise::Reseedable;

class TilePartitionerPerlin : public TilePartitionerBase
{
public:
    TilePartitionerPerlin(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    void makeCorner(noise::NoiseMapVector<float> & noise_map_vector,
                    const Corners& corners,
                    bool left, bool top);
protected:
    noise::ModuleManager mNoiseModuleManager;
};
