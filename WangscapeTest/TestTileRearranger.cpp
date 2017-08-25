#include <gtest/gtest.h>
#include "DocumentationPath.h"
#include <boost/filesystem.hpp>
#include <image/TileRearranger.h>

class TestTileRearranger : public ::testing::Test
{
protected:
    void expectImagesEqual(const ImageGrey& expected, const ImageGrey& actual, const std::string& message="")
    {
        const auto equality = (expected == actual).eval();
        if (equality.min() == equality.max() == 1)
            return;
        auto fail_indices = arma::find(equality != 1);
        auto fail_coords = arma::ind2sub(arma::size(equality), fail_indices);
        EXPECT_TRUE(false) << message <<"\nFirst failure location: " <<
            "y " << fail_coords(0,0) << ", " <<
            "x " << fail_coords(1,0);
    }
    void saveBinaryImage(const ImageGrey& image, const std::string& filename)
    {
        imageBinaryToSFImage(image).saveToFile(filename);
    }
    void saveImage(const ImageGrey& image, const std::string& filename)
    {
        imageToSFImage(imageGreyscaleToImage(image)).saveToFile(filename);
    }
    sf::Image imageBinaryToSFImage(const ImageGrey& image)
    {
        return imageToSFImage(imageGreyscaleToImage(image * 255));
    }
    void expectSFImagesEqual(const sf::Image& expected, const sf::Image& actual, const std::string& message = "")
    {
        EXPECT_EQ(expected.getSize(), actual.getSize());
        const auto shape = actual.getSize();
        for (size_t y = 0; y < shape.y; y++)
        {
            for (size_t x = 0; x < shape.x; x++)
            {
                EXPECT_EQ(expected.getPixel(x, y), actual.getPixel(x, y)) << message << "\n" <<
                    "at " << x << ", " << y;
            }
        }
    }
};

TEST_F(TestTileRearranger, TestIsConnected)
{
    ImageGrey disconnected = {{1, 0, 1}, {1, 0, 1}};
    ImageGrey connected = {{1, 0, 1}, {1, 1, 1}};
    ImageGrey diagonally_connected = {{1, 0, 1}, {0, 1, 0}};
    EXPECT_TRUE(isConnected(connected));
    EXPECT_FALSE(isConnected(disconnected));
    EXPECT_FALSE(isConnected(diagonally_connected, false));
    EXPECT_TRUE(isConnected(diagonally_connected, true));
}

TEST_F(TestTileRearranger, TestDistances)
{
    arma::u32 infinity = std::numeric_limits<arma::u32>::max();
    ImageGrey traversable = {{1, 0, 1}, {1, 0, 1}, {1, 1, 1}};
    ImageGrey targets = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    ImageGrey distance = {{0, 255, 6}, {1, 255, 5}, {2, 3, 4}};
    ImageGrey distance_diagonal = {{0, 255, 4}, {1, 255, 3}, {2, 2, 3}};

    ImageGrey32 computed_distance = distances(traversable, targets, false);
    computed_distance.replace(infinity, 255);
    ImageGrey32 computed_distance_diagonal = distances(traversable, targets, true);
    computed_distance_diagonal.replace(infinity, 255);
    expectImagesEqual(distance, arma::conv_to<ImageGrey>::from(computed_distance), "incorrect distance");
    expectImagesEqual(distance_diagonal, arma::conv_to<ImageGrey>::from(computed_distance_diagonal), "incorrect distance (diagonal)");
}

TEST_F(TestTileRearranger, TestDistances2)
{
    arma::u32 infinity = std::numeric_limits<arma::u32>::max();
    ImageGrey traversable = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    ImageGrey targets = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
    ImageGrey distance = {{255, 255, 255, 255}, {255, 2, 1, 255}, {255, 1, 0, 255}, {255, 255, 255, 255}};
    ImageGrey distance_diagonal = {{255, 255, 255, 255}, {255, 1, 1, 255}, {255, 1, 0, 255}, {255, 255, 255, 255}};

    ImageGrey32 computed_distance = distances(traversable, targets, false);
    computed_distance.replace(infinity, 255);
    ImageGrey32 computed_distance_diagonal = distances(traversable, targets, true);
    computed_distance_diagonal.replace(infinity, 255);
    expectImagesEqual(distance, arma::conv_to<ImageGrey>::from(computed_distance), "incorrect distance");
    expectImagesEqual(distance_diagonal, arma::conv_to<ImageGrey>::from(computed_distance_diagonal), "incorrect distance (diagonal)");
}

TEST_F(TestTileRearranger, TestIsNonzero)
{
    ImageGrey zero = {{0, 0}, {0, 0}};
    ImageGrey binary = {{0, 1}, {1, 0}};
    ImageGrey nonzero = {{0, 255}, {1, 0}};
    EXPECT_FALSE(isNonzero(zero));
    EXPECT_TRUE(isNonzero(binary));
    EXPECT_TRUE(isNonzero(nonzero));
}

TEST_F(TestTileRearranger, TestIsBinary)
{
    ImageGrey zero = {{0, 0}, {0, 0}};
    ImageGrey binary = {{0, 1}, {1, 0}};
    ImageGrey nonzero = {{0, 255}, {1, 0}};
    EXPECT_TRUE(isBinary(zero));
    EXPECT_TRUE(isBinary(binary));
    EXPECT_FALSE(isBinary(nonzero));
}

TEST_F(TestTileRearranger, TestPadded)
{
    ImageGrey image = {{1, 2}};
    ImageGrey image_padded = {{0, 0, 0, 0}, {0, 1, 2, 0}, {0, 0, 0, 0}};
    expectImagesEqual(image_padded, padded(image));
}

TEST_F(TestTileRearranger, TestUnpadded)
{
    ImageGrey image = {{1, 2}};
    ImageGrey image_padded = {{3, 4, 5, 6}, {7, 1, 2, 8}, {9, 10, 11, 12}};
    expectImagesEqual(image, unpadded(image_padded));
}

TEST_F(TestTileRearranger, TestDilatedEroded)
{
    ImageGrey zero = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
    ImageGrey image = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
    ImageGrey image_dilated = {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
    ImageGrey image_dilated_diagonal = {{0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}};
    expectImagesEqual(image_dilated, dilated(image, false), "incorrect dilation");
    expectImagesEqual(image_dilated_diagonal, dilated(image, true), "incorrect diagonal dilation");
    expectImagesEqual(image, eroded(image_dilated, false), "incorrect erosion");
    expectImagesEqual(image, eroded(image_dilated_diagonal, true), "incorrect diagonal erosion");
}

TEST_F(TestTileRearranger, TestBoundary)
{
    ImageGrey solid = {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
    ImageGrey hollow = {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
    ImageGrey solid_diagonal = {{0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}};
    ImageGrey hollow_diagonal = {{0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}};
    expectImagesEqual(hollow, boundary(solid, false), "incorrect boundary of cross");
    expectImagesEqual(solid, boundary(solid, true), "incorrect boundary (diagonal) of cross");
    expectImagesEqual(hollow_diagonal, boundary(solid_diagonal, false), "incorrect boundary");
    expectImagesEqual(hollow_diagonal, boundary(solid_diagonal, true), "incorrect boundary (diagonal)");
}

TEST_F(TestTileRearranger, TestNeighbourhoodIntersection)
{
    ImageGrey neighbours = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    ImageGrey mask = {{1, 1, 1}, {1, 1, 1}, {0, 0, 0}};
    ImageGrey neighbourhood_intersection = {{0, 0, 0}, {0, 0, 1}, {0, 0, 0}};
    ImageGrey neighbourhood_intersection_diagonal = {{0, 0, 0}, {0, 1, 1}, {0, 0, 0}};
    expectImagesEqual(neighbourhood_intersection, neighbourhoodIntersection(mask, neighbours, false));
    expectImagesEqual(neighbourhood_intersection_diagonal, neighbourhoodIntersection(mask, neighbours, true));
}

TEST_F(TestTileRearranger, TestRegionBox)
{
    ImageGrey image = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    sf::IntRect bbox{1, 2, 2, 1};
    EXPECT_EQ(bbox, regionBox(image));
}

TEST_F(TestTileRearranger, TestBoxUnion)
{
    sf::IntRect bbox_a{1, 2, 2, 1};
    sf::IntRect bbox_b{2, 2, 1, 2};
    sf::IntRect bbox_union{1, 2, 2, 2};
    EXPECT_EQ(bbox_union, boxUnion(bbox_a, bbox_b));
}

TEST_F(TestTileRearranger, TestCopyRegion)
{
    ImageGrey zeros(2, 2, arma::fill::zeros);
    ImageGrey ones(2, 2, arma::fill::ones);
    {
        ImageGrey image = zeros;
        copyRegion(ones, image, {0, 0}, {0, 0}, {2, 2});
        expectImagesEqual(ones, image, "incorrect 2x2 region copy");
    }
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{0, 1}, {0, 0}};
        copyRegion(ones, image, {0, 0}, {1, 0}, {1, 1});
        expectImagesEqual(expected, image, "incorrect 1x1 region copy");
    }
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{0, 0}, {1, 1}};
        copyRegion(ones, image, {0, 0}, {0, 1}, {2, 1});
        expectImagesEqual(expected, image, "incorrect 2x1 region copy");
    }
}

TEST_F(TestTileRearranger, TestCopyRegionBounded)
{
    ImageGrey zeros(2, 2, arma::fill::zeros);
    ImageGrey ones(2, 2, arma::fill::ones);
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{1, 0}, {0, 0}};
        copyRegionBounded(ones, image, {0, 0}, {-1, -1}, {2, 2});
        expectImagesEqual(expected, image, "incorrect top left bounded region copy");
    }
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{0, 1}, {0, 0}};
        copyRegionBounded(ones, image, {0, 0}, {1, -1}, {2, 2});
        expectImagesEqual(expected, image, "incorrect top right bounded region copy");
    }
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{0, 0}, {1, 0}};
        copyRegionBounded(ones, image, {0, 0}, {-1, 1}, {2, 2});
        expectImagesEqual(expected, image, "incorrect bottom left bounded region copy");
    }
    {
        ImageGrey image = zeros;
        ImageGrey expected = {{0, 0}, {0, 1}};
        copyRegionBounded(ones, image, {0, 0}, {1, 1}, {2, 2});
        expectImagesEqual(expected, image, "incorrect bottom right bounded region copy");
    }
}

TEST_F(TestTileRearranger, TestTileRearrangerMinimal)
{
    TileRearranger tr;
    sf::Image i;
    i.create(2, 2);
    i.setPixel(0, 0, sf::Color::Red);
    i.setPixel(1, 0, sf::Color::Green);
    i.setPixel(1, 1, sf::Color::Blue);
    i.setPixel(0, 1, sf::Color::Yellow);
    const auto rearrangement = tr.rearrangeTile(i, {2, 0}, {0, 2});
    sf::Image d = rearrangement.rearrangeTexture(i);
    EXPECT_EQ(makeUVec(d.getSize()), UVec(2, 2)) << "Wrong size dual tile";

    EXPECT_EQ(rearrangement.dualPartition(1, 1, 0), 1) << "Wrong dual partition";
    EXPECT_EQ(rearrangement.dualPartition(1, 0, 1), 1) << "Wrong dual partition";
    EXPECT_EQ(rearrangement.dualPartition(0, 0, 2), 1) << "Wrong dual partition";
    EXPECT_EQ(rearrangement.dualPartition(0, 1, 3), 1) << "Wrong dual partition";

    EXPECT_EQ(d.getPixel(1, 1), sf::Color::Red) << "Wrong pixel in dual tile";
    EXPECT_EQ(d.getPixel(0, 1), sf::Color::Green) << "Wrong pixel in dual tile";
    EXPECT_EQ(d.getPixel(0, 0), sf::Color::Blue) << "Wrong pixel in dual tile";
    EXPECT_EQ(d.getPixel(1, 0), sf::Color::Yellow) << "Wrong pixel in dual tile";

    for (unsigned int c = 0; c < 4; c++)
    {
        expectImagesEqual(rearrangement.dualPartition.slice(c), rearrangement.dualCorners.slice(c), "incorrect dual corner");
    }
    expectImagesEqual(rearrangement.dualEdges.slice(0),
                      rearrangement.dualCorners.slice(0) + rearrangement.dualCorners.slice(1), "incorrect dual edge");
    expectImagesEqual(rearrangement.dualEdges.slice(1),
                      rearrangement.dualCorners.slice(1) + rearrangement.dualCorners.slice(2), "incorrect dual edge");
    expectImagesEqual(rearrangement.dualEdges.slice(2),
                      rearrangement.dualCorners.slice(2) + rearrangement.dualCorners.slice(3), "incorrect dual edge");
    expectImagesEqual(rearrangement.dualEdges.slice(3),
                      rearrangement.dualCorners.slice(3) + rearrangement.dualCorners.slice(0), "incorrect dual edge");
    const auto distance_corners = rearrangement.getCornerDistances(true);
    for (unsigned int c = 0; c < 4; c++)
    {
        ImageGrey distance_this_corner_8 = arma::conv_to<ImageGrey>::from(
            distance_corners.slice(c)).eval();
        expectImagesEqual(
            rearrangement.dualCorners.slice(c),
            (1 - distance_this_corner_8).eval(),
            "incorrect corner distance");
        // Uncomment to get output in working directory.
        // saveBinaryImage(distance_this_corner_8, "mdcorner" + std::to_string(c) + ".png");
    }
    const auto distance_edges = rearrangement.getEdgeDistances(true);
    for (unsigned int e = 0; e < 4; e++)
    {
        ImageGrey distance_this_edge_8 = arma::conv_to<ImageGrey>::from(
            distance_edges.slice(e)).eval();
        expectImagesEqual(rearrangement.dualEdges.slice((e+2)%4),
                          distance_this_edge_8,
                          "incorrect edge distance");
        // Uncomment to get output in working directory.
        // saveBinaryImage(distance_this_edge_8, "mdedge" + std::to_string(e) + ".png");

    }
}

TEST_F(TestTileRearranger, TestTileRearrangerComplex)
{
    const auto test_path = boost::filesystem::path(getDocumentationPath()) / "tests" / "rearranger";
    sf::Image base;
    base.loadFromFile((test_path / "base.png").string());
    const auto rearrangement = TileRearranger().rearrangeTile(base, {80, 0}, {0, 80});
    sf::Image dual;
    dual.loadFromFile((test_path / "dual.png").string());
    sf::Image computed_dual = rearrangement.rearrangeTexture(base);
    // Uncomment to get output in working directory.
    // computed_dual.saveToFile("dual_complex.png");
    expectSFImagesEqual(dual, computed_dual, "incorrect dual");
    for (unsigned int c = 0; c < 4; c++)
    {
        sf::Image corner;
        corner.loadFromFile((test_path / ("corner" + std::to_string(c) + ".png")).string());
        expectSFImagesEqual(corner, 
                            imageBinaryToSFImage(rearrangement.dualCorners.slice(c)),
                            "incorrect corner " + std::to_string(c));
        // Uncomment to get output in working directory.
        // saveBinaryImage(rearrangement.dualCorners.slice(c), "corner" + std::to_string(c) + ".png");
    }
    for (unsigned int e = 0; e < 4; e++)
    {
        sf::Image edge;
        edge.loadFromFile((test_path / ("edge" + std::to_string(e) + ".png")).string());
        expectSFImagesEqual(edge,
                            imageBinaryToSFImage(rearrangement.dualEdges.slice(e)),
                            "incorrect edge " + std::to_string(e));
        // Uncomment to get output in working directory.
        // saveBinaryImage(rearrangement.dualEdges.slice(e), "edge" + std::to_string(e) + ".png");
    }
    auto distance_corners_32 = rearrangement.getCornerDistances(false);
    distance_corners_32.replace(std::numeric_limits<arma::u32>::max(), 0);
    const auto distance_corners = arma::conv_to<ImageStackGrey>::from(distance_corners_32);
    for (unsigned int c = 0; c < 4; c++)
    {
        sf::Image corner_distance;
        corner_distance.loadFromFile((test_path / ("dcorner" + std::to_string(c) + ".png")).string());
        expectSFImagesEqual(corner_distance,
                            imageToSFImage(imageGreyscaleToImage(distance_corners.slice(c))),
                            "incorrect corner distance " + std::to_string(c));
        // Uncomment to get output in working directory.
        //saveImage(distance_corners.slice(c), "dcorner" + std::to_string(c) + ".png");
    }
    auto distance_edges_32 = rearrangement.getEdgeDistances(false);
    distance_edges_32.replace(std::numeric_limits<arma::u32>::max(), 0);
    const auto distance_edges = arma::conv_to<ImageStackGrey>::from(distance_edges_32);
    for (unsigned int c = 0; c < 4; c++)
    {
        sf::Image edge_distance;
        edge_distance.loadFromFile((test_path / ("dedge" + std::to_string(c) + ".png")).string());
        expectSFImagesEqual(edge_distance,
                            imageToSFImage(imageGreyscaleToImage(distance_edges.slice(c))),
                            "incorrect edge distance " + std::to_string(c));
        // Uncomment to get output in working directory.
        //saveImage(distance_edges.slice(c), "dedge" + std::to_string(c) + ".png");
    }
}
