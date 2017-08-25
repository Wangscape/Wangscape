#pragma once

#include "Image.h"

class TileRearrangement
{
public:
    TileRearrangement() = default;
    ImageGrey base;
    ImageGrey dual;
    ImageStackGrey basePartition;
    ImageStackGrey dualPartition;
    ImageStackGrey dualEdges;
    ImageStackGrey dualCorners;
    UVec baseSize;
    IVec offsetA;
    IVec offsetB;
    IVec dualOffset;
    std::vector<IVec> allOffsets;
    UVec dualSize;

    sf::Image rearrangeTexture(const sf::Image& base_texture) const;
    ImageStackGrey32 getCornerDistances(bool use_diagonals) const;
    ImageStackGrey32 getEdgeDistances(bool use_diagonals) const;
};
