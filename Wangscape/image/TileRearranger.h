#pragma once
#include <array>

#include "Image.h"
#include "TileRearrangement.h"

template<unsigned int Corners>
class TileRearranger
{
public:
    TileRearranger();
    ~TileRearranger() = default;

    const TileRearrangement rearrangeTile(const sf::Image& base_tile,
                                          IVec offset_a,
                                          IVec offset_b);

    std::array<sf::Color, Corners> regionColours;

private:
    static constexpr unsigned int dualCorners();
    void decomposeBaseTile(const sf::Image& base_tile);
    void validateBaseTile() const;
    void validateColours() const;
    static void validateTessellation(const ImageStackGrey& tessellation);
    void findDualBoundaries(const ImageStackGrey& dual_tessellation);
    void calculateRearrangementParameters();
    void makeDual();
    std::vector<IVec> makeTessellationOffsets() const;
    TileRearrangement mTileRearrangement;
};
