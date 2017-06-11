#include "TilePartitionerBase.h"

namespace tilegen
{
namespace partition
{

TilePartitionerBase::TilePartitionerBase(const Options & options) :
    mOptions(options)
{
}

void TilePartitionerBase::setDebugModuleWriter(DebugModuleWriter& debugModuleWriter)
{
    mDebugModuleWriter = debugModuleWriter;
}

} // namespace partition
} // namespace tilegen
