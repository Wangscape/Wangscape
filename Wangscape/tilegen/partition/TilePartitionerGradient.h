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
    int gradientWeight(sf::Vector2u xy, sf::Vector2u corner, sf::Vector2u margin = {0, 0});
};

} // namespace partition
} // namespace tilegen
