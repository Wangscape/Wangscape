#pragma once
#include "TilePartitionerBase.h"
#include <SFML/Graphics.hpp>

class TilePartitionerGradient : public TilePartitionerBase
{
public:
    TilePartitionerGradient(const Options& options);
    virtual void makePartition(TilePartition& regions, const Corners& corners);
    int gradientWeight(int x, int y, int x_corner, int y_corner, int margin = 0);
protected:

};
