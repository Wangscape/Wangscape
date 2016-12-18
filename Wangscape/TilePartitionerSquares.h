#pragma once
#include "TilePartitionerBase.h"

class TilePartitionerSquares : public TilePartitionerBase
{
public:
    TilePartitionerSquares(const Options& options);
    virtual void makePartition(TilePartition& regions, const Corners& corners);
protected:

};
