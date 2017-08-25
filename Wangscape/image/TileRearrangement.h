#pragma once

#include "Image.h"

class TileRearrangement
{
public:
    TileRearrangement() = default;
    // Base tile mask
    ImageGrey base;
    // Dual tile mask
    ImageGrey dual;
    // Partition of base tile
    ImageStackGrey basePartition;
    // Partition of dual tile
    ImageStackGrey dualPartition;
    // Edges of dual tile
    ImageStackGrey dualEdges;
    // Corners of dual tile
    ImageStackGrey dualCorners;
    // Size of base tile
    UVec baseSize;
    // "Horizontal" offset for tessellating the tile
    IVec offsetA;
    // "Vertical" offset for tessellating the tile
    IVec offsetB;
    // Offset of dual tile origin relative to base tile origin
    IVec dualOffset;
    // Offset of each partition region when translating from base tile to dual tile
    std::vector<IVec> allOffsets;
    // Size of dual tile
    UVec dualSize;

    // Rearranges the input texture according to the conversion from base tile to dual tile
    sf::Image rearrangeTexture(const sf::Image& base_texture) const;
    // Returns a 32-bit greyscale image stack. Each layer contains the distance of each pixel in the dual tile from a tile corner.
    ImageStackGrey32 getCornerDistances(bool use_diagonals) const;
    // Returns a 32-bit greyscale image stack. Each layer contains the distance of each pixel in the dual tile from a tile edge.
    ImageStackGrey32 getEdgeDistances(bool use_diagonals) const;
};
