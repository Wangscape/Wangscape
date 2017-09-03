#include "TileRearranger.h"
#include <set>
#include "logging/Logging.h"
const static std::array<sf::Color, 6> default_region_colours{
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta};

TileRearranger::TileRearranger()
{
    for (int i = 0; i < Corners; i++)
        regionColours[i] = default_region_colours[i];
}

const TileRearrangement TileRearranger::rearrangeTile(const sf::Image & base_tile,
                                                      IVec offset_a,
                                                      IVec offset_b)
{
    // Initialise vectors
    mTileRearrangement.offsetA = offset_a;
    mTileRearrangement.offsetB = offset_b;
    mTileRearrangement.baseSize = makeUVec(base_tile.getSize());

    // Check all region colours are unique
    validateColours();
    // Convert base tile image into stack of partition masks
    decomposeBaseTile(base_tile);
    // Check base tile regions are nonempty and nonoverlapping
    validateBaseTile();

    // Tessellate padded version of base tile in 3x3 grid 
    const auto tessellation_offsets = makeTessellationOffsets();
    const auto base_tessellation = tessellated(mTileRearrangement.base, tessellation_offsets);
    // Check that tessellation has no holes or overlaps
    validateTessellation(base_tessellation);

    // Find bounding box of dual tile in base tile coordinates
    calculateRearrangementParameters();
    // Translate each region of the base tile partition into dual tile partition, and assemble them
    makeDual();

    // Tessellate padded version of dual tile in 3x3 grid
    const auto dual_tessellation = tessellated(mTileRearrangement.dual, tessellation_offsets);
    // Check that tessellation has no holes or overlaps
    validateTessellation(dual_tessellation);

    // Use adjacency between dual tile mask and offset versions to find edges and corners of dual tile mask
    findDualBoundaries(dual_tessellation);

    return mTileRearrangement;
}

void TileRearranger::decomposeBaseTile(const sf::Image & base_tile)
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
        const auto not_function = [](bool x) { return !x; };
        channel_matches.transform(not_function);
        ImageGrey pixel_matches = arma::sum(channel_matches, 2);
        pixel_matches.transform(not_function);
        mTileRearrangement.basePartition.slice(c) = pixel_matches;
    }
    mTileRearrangement.base = arma::sum(mTileRearrangement.basePartition, 2);
}

void TileRearranger::validateBaseTile() const
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

void TileRearranger::validateColours() const
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

void TileRearranger::validateTessellation(const ImageStackGrey & tessellation)
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

void TileRearranger::findDualBoundaries(const ImageStackGrey& dual_tessellation)
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

void TileRearranger::calculateRearrangementParameters()
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

void TileRearranger::makeDual()
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

std::vector<IVec> TileRearranger::makeTessellationOffsets() const
{
    std::vector<IVec> offsets;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            offsets.push_back(x*mTileRearrangement.offsetA + y*mTileRearrangement.offsetB);
        }
    }
    return offsets;
}

TileRearrangement rectangularRearrangement(UVec size)
{
    ImageColour base_tile_array(size.y(), size.x(), 4);
    const UVec middle = size / 2;

    const auto set_rectangle = [&base_tile_array](sf::Color colour, arma::span x_span, arma::span y_span)
    {
        base_tile_array.slice(0).submat(y_span, x_span).fill(arma::u8(colour.r));
        base_tile_array.slice(1).submat(y_span, x_span).fill(arma::u8(colour.g));
        base_tile_array.slice(2).submat(y_span, x_span).fill(arma::u8(colour.b));
        base_tile_array.slice(3).submat(y_span, x_span).fill(arma::u8(colour.a));
    };
    set_rectangle(sf::Color::Red, arma::span(0, middle.x() - 1), arma::span(0, middle.y() - 1));
    set_rectangle(sf::Color::Green, arma::span(middle.x(), size.x() - 1), arma::span(0, middle.y() - 1));
    set_rectangle(sf::Color::Blue, arma::span(middle.x(), size.x() - 1), arma::span(middle.y(), size.y() - 1));
    set_rectangle(sf::Color::Yellow, arma::span(0, middle.x() - 1), arma::span(middle.y(), size.y() - 1));

    sf::Image base_tile = imageToSFImage(base_tile_array);

    return TileRearranger().rearrangeTile(base_tile, IVec(size.x(), 0), IVec(0, size.y()));
}
