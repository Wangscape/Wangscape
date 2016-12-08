#include "TilePartition.h"

TilePartition::TilePartition(std::vector<Options::TerrainID> corners, const Options& options)
{
    initialise(corners, options);
}

TilePartition::~TilePartition()
{

}