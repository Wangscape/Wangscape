#pragma once
#include "TilePartitionerBase.h"
#include <SFML/Graphics.hpp>

namespace tilegen
{
namespace partition
{

class TilePartitionerGradient : public TilePartitionerBase
{
public:
    using TilePartitionerBase::TilePartitionerBase;
    virtual void makePartition(TilePartition& regions, const Corners& corners);
    int gradientWeight(int x, int y, int x_corner, int y_corner, int margin = 0);
};

} // namespace partition
} // namespace tilegen
