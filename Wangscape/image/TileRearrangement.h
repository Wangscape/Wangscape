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
    sf::Vector2u baseSize;
    sf::Vector2i offsetA;
    sf::Vector2i offsetB;
    sf::Vector2i dualOffset;
    std::vector<sf::Vector2i> allOffsets;
    sf::Vector2u dualSize;

    sf::Image rearrangeTexture(const sf::Image& base_texture) const;
    ImageStackGrey32 getCornerDistances(bool use_diagonals) const;
    ImageStackGrey32 getEdgeDistances(bool use_diagonals) const;
};
