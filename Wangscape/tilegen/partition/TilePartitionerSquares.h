#pragma once
#include "TilePartitionerBase.h"

class TilePartitionerSquares : public TilePartitionerBase
{
public:
    using TilePartitionerBase::TilePartitionerBase;
    virtual void makePartition(TilePartition& regions, const Corners& corners);
protected:

};
