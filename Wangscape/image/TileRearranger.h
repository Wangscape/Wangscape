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
                                          sf::Vector2i offset_a,
                                          sf::Vector2i offset_b);

    std::array<sf::Color, Corners> regionColours;

private:
    static constexpr unsigned int dualCorners();
    void decomposeBaseTile(const sf::Image& base_tile);
    void validateBaseTile() const;
    void validateColours() const;
    ImageStackGrey tessellated(const ImageGrey& image) const;
    static void validateTessellation(const ImageStackGrey& tessellation);
    void findDualBoundaries(const ImageStackGrey& dual_tessellation);
    void calculateRearrangementParameters();
    void makeDual();
    TileRearrangement mTileRearrangement;
};

