#pragma once
#include "TilePartitionerBase.h"

namespace tilegen
{
namespace partition
{

class TilePartitionerSquares : public TilePartitionerBase
{
public:
    using TilePartitionerBase::TilePartitionerBase;
    virtual void makePartition(TilePartition& regions, const Corners& corners);
protected:

};

} // namespace partition
} // namespace tilegen
