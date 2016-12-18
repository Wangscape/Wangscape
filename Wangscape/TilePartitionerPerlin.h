#pragma once
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "NoiseModuleManager.h"
#include "TilePartitionerBase.h"

class TilePartitionerPerlin : public TilePartitionerBase
{
public:
    TilePartitionerPerlin(const Options& options);
    void makePartition(TilePartition& regions,
                       const Corners& corners);
    void makeCorner(TilePartition & regions, const Corners& corners,
                    bool left, bool top);
protected:
    NoiseModuleManager mNoiseModuleManager;
};
