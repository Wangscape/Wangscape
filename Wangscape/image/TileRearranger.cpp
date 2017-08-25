#include "TileRearranger.h"
#include <set>
#include "Logging/Logging.h"
const static std::array<sf::Color, 6> default_region_colours{
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta};

template<unsigned int Corners>
TileRearranger<Corners>::TileRearranger()
{
    for (int i = 0; i < Corners; i++)
        regionColours[i] = default_region_colours[i];
}

template<unsigned int Corners>
const TileRearrangement TileRearranger<Corners>::rearrangeTile(const sf::Image & base_tile,
                                                      IVec offset_a,
                                                      IVec offset_b)
{
    mTileRearrangement.offsetA = offset_a;
    mTileRearrangement.offsetB = offset_b;
    mTileRearrangement.baseSize = makeUVec(base_tile.getSize());
    validateColours();

    decomposeBaseTile(base_tile);
    validateBaseTile();

    const auto tessellation_offsets = makeTessellationOffsets();
    const auto base_tessellation = tessellated(mTileRearrangement.base, tessellation_offsets);
    validateTessellation(base_tessellation);

    calculateRearrangementParameters();
    makeDual();

    const auto dual_tessellation = tessellated(mTileRearrangement.dual, tessellation_offsets);
    validateTessellation(dual_tessellation);

    findDualBoundaries(dual_tessellation);

    return mTileRearrangement;
}

template<unsigned int Corners>
constexpr unsigned int TileRearranger<Corners>::dualCorners()
{
    return (Corners == 3) ? 6 :
        (Corners == 4) ? 4 :
        (Corners == 6) ? 3 :
        0;
}

template<unsigned int Corners>
void TileRearranger<Corners>::decomposeBaseTile(const sf::Image & base_tile)
{
    const auto base_tile_cube = imageFromSFImage(base_tile);
    mTileRearrangement.basePartition.set_size(base_tile_cube.n_rows,
                                               base_tile_cube.n_cols,
                                               Corners);
    for (unsigned int c = 0; c < Corners; c++)
    {
        auto uniform_colour_cube = ImageColour(arma::size(base_tile_cube));
        uniform_colour_cube.slice(0).fill(regionColours[c].r);
        uniform_colour_cube.slice(1).fill(regionColours[c].g);
        uniform_colour_cube.slice(2).fill(regionColours[c].b);
        uniform_colour_cube.slice(3).fill(regionColours[c].a);
        ImageStackGrey channel_matches = arma::conv_to<ImageStackGrey>::from(
            (base_tile_cube == uniform_colour_cube).eval());
        // Armadillo doesn't have a product or general reducer function,
        // so we have to use sum instead.
        const auto not = [](bool x) { return !x; };
        channel_matches.transform(not);
        ImageGrey pixel_matches = arma::sum(channel_matches, 2);
        pixel_matches.transform(not);
        mTileRearrangement.basePartition.slice(c) = pixel_matches;
    }
    mTileRearrangement.base = arma::sum(mTileRearrangement.basePartition, 2);
}

template<unsigned int Corners>
void TileRearranger<Corners>::validateBaseTile() const
{
    if (!isNonzero(mTileRearrangement.base))
    {
        logError() << "Base tile empty";
        throw std::runtime_error("Base tile empty");
    }
    if (!isBinary(mTileRearrangement.base))
    {
        logError() << "Base tile has overlapping regions";
        throw std::runtime_error("Base tile not correctly partitioned");
    }
    if (!isConnected(mTileRearrangement.base))
    {
        logError() << "Base tile not connected";
        throw std::runtime_error("Base tile not connected");
    }
    for (unsigned int c = 0; c < Corners; c++)
    {
        if (!isNonzero(mTileRearrangement.basePartition.slice(c)))
        {
            logError() << "Base tile region " << c << " empty";
            throw std::runtime_error("Base tile region empty");
        }
        if (!isConnected(mTileRearrangement.basePartition.slice(c)))
        {
            logError() << "Base tile " << c << " not connected";
            throw std::runtime_error("Base tile region not connected");
        }
    }
}

template<unsigned int Corners>
void TileRearranger<Corners>::validateColours() const
{
    const auto less = [](sf::Color x, sf::Color y) {return x.toInteger() < y.toInteger(); };
    std::set <sf::Color, decltype(less)> colours_set(less);
    for (const auto c : regionColours)
        colours_set.insert(c);
    if (regionColours.size() != colours_set.size())
    {
        logError() << "Can't rearrange base tile; region colours not distinct";
        throw std::runtime_error("Region colours not distinct");
    }
}

template<unsigned int Corners>
void TileRearranger<Corners>::validateTessellation(const ImageStackGrey & tessellation)
{
    if (tessellation.max() > 1)
    {
        logError() << "Tessellation is not binary";
        throw std::runtime_error("Error creating tessellation");
    }
    if (!isBinary(arma::sum(tessellation, 2).eval()))
    {
        logError() << "Base tile causes overlap when tessellated";
        throw std::runtime_error("Can't tessellate base tile");
    }
    const auto central_boundary = boundary(tessellation.slice(4));
    ImageStackGrey surround(tessellation);
    surround.shed_slice(4);
    ImageGrey surround_sum = arma::sum(surround, 2).eval();
    ImageGrey hole_neighbours = arma::conv_to<ImageGrey>::from(
        (neighbourhoodIntersection(central_boundary, surround_sum) != central_boundary).eval()).eval();
    if (hole_neighbours.max() != 0)
    {
        logError() << "Base tile leaves a hole when tessellated";
        throw std::runtime_error("Can't tessellate base tile");
    }
}

template<unsigned int Corners>
void TileRearranger<Corners>::findDualBoundaries(const ImageStackGrey& dual_tessellation)
{
    ImageGrey central_boundary = boundary(dual_tessellation.slice(4));
    std::array<unsigned int, Corners> corner_codes{8, 6, 0, 2};
    std::array<unsigned int, Corners> edge_codes{7, 3, 1, 5};
    mTileRearrangement.dualEdges.set_size(dual_tessellation.n_rows, dual_tessellation.n_cols, Corners);
    for (unsigned int e = 0; e < Corners; e++)
    {
        mTileRearrangement.dualEdges.slice(e) = neighbourhoodIntersection(central_boundary,
                                                                          dual_tessellation.slice(edge_codes[e]),
                                                                          false);
    }
    ImageStackGrey opposites(dual_tessellation.n_rows, dual_tessellation.n_cols, Corners);
    for (unsigned int c = 0; c < Corners; c++)
    {
        opposites.slice(c) = neighbourhoodIntersection(central_boundary,
                                                       dual_tessellation.slice(corner_codes[c]),
                                                       false);
    }
    mTileRearrangement.dualCorners.set_size(arma::size(mTileRearrangement.dualEdges));
    mTileRearrangement.dualCorners = mTileRearrangement.dualEdges;
    for (unsigned int c = 0; c < Corners; c++)
    {
        mTileRearrangement.dualCorners.slice(c) %= mTileRearrangement.dualEdges.slice((c + Corners - 1) % Corners);
    }
    mTileRearrangement.dualCorners += opposites;
    mTileRearrangement.dualCorners.transform([](arma::u8 x) {return std::min(x, arma::u8(1)); });

    mTileRearrangement.dualCorners = unpaddedStack(mTileRearrangement.dualCorners);
    mTileRearrangement.dualEdges = unpaddedStack(mTileRearrangement.dualEdges);
}

template<unsigned int Corners>
void TileRearranger<Corners>::calculateRearrangementParameters()
{
    std::array<sf::IntRect, Corners> corner_bboxes;
    for (int c = 0; c < Corners; c++)
    {
        corner_bboxes[c] = regionBox(mTileRearrangement.basePartition.slice(c));
    }
    // Depends on Corners
    mTileRearrangement.allOffsets = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};
    for (auto& offset : mTileRearrangement.allOffsets)
    {
        offset = offset.x() * mTileRearrangement.offsetA + offset.y() * mTileRearrangement.offsetB;
    }
    std::array<sf::IntRect, Corners> dual_corner_bboxes;
    for (unsigned int c = 0; c < Corners; c++)
    {
        dual_corner_bboxes[c] = corner_bboxes[c];
        dual_corner_bboxes[c].left += mTileRearrangement.allOffsets[c].x();
        dual_corner_bboxes[c].top += mTileRearrangement.allOffsets[c].y();
    }
    auto dual_bbox = dual_corner_bboxes[0];
    for (unsigned int c = 1; c < Corners; c++)
    {
        dual_bbox = boxUnion(dual_bbox, dual_corner_bboxes[c]);
    }
    mTileRearrangement.dualSize = {(unsigned int)dual_bbox.width, (unsigned int)dual_bbox.height};
    mTileRearrangement.dualOffset = {dual_bbox.left, dual_bbox.top};
}

template<unsigned int Corners>
void TileRearranger<Corners>::makeDual()
{
    mTileRearrangement.dualPartition.set_size(mTileRearrangement.dualSize.y(),
                                              mTileRearrangement.dualSize.x(),
                                              Corners);
    mTileRearrangement.dualPartition.fill(0);
    for (unsigned int c = 0; c < Corners; c++)
    {
        copyRegionBounded(mTileRearrangement.basePartition.slice(c),
                          mTileRearrangement.dualPartition.slice(c),
                          {0, 0},
                          mTileRearrangement.allOffsets[c] - mTileRearrangement.dualOffset,
                          IVec(mTileRearrangement.baseSize));
    }
    mTileRearrangement.dual = arma::sum(mTileRearrangement.dualPartition, 2).eval();
}

template<unsigned int Corners>
std::vector<IVec> TileRearranger<Corners>::makeTessellationOffsets() const
{
    std::vector<IVec> offsets;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            offsets.push_back((x - 1)*mTileRearrangement.offsetA + (y - 1)*mTileRearrangement.offsetB);
        }
    }
    return offsets;
}

// template class TileRearranger<3>;
template class TileRearranger<4>;
// template class TileRearranger<6>;
