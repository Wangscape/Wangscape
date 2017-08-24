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
    TileRearranger<4> tr;
    sf::Image i;
    i.create(2, 2);
    i.setPixel(0, 0, sf::Color::Red);
    i.setPixel(1, 0, sf::Color::Green);
    i.setPixel(1, 1, sf::Color::Blue);
    i.setPixel(0, 1, sf::Color::Yellow);
    const auto rearrangement = tr.rearrangeTile(i, {0, 2}, {2, 0});
    sf::Image d = rearrangement.rearrangeTexture(i);
    EXPECT_EQ(d.getSize(), sf::Vector2u(2, 2)) << "Wrong size dual tile";

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

}

TEST_F(TestTileRearranger, TestTileRearrangerComplex)
{
    const auto test_path = boost::filesystem::path(getDocumentationPath()) / "tests" / "rearranger";
    sf::Image base;
    base.loadFromFile((test_path / "base.png").string());
    const auto rearrangement = TileRearranger<4>().rearrangeTile(base, {0, 80}, {80, 0});
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
    }
    for (unsigned int e = 0; e < 4; e++)
    {
        sf::Image edge;
        edge.loadFromFile((test_path / ("edge" + std::to_string(e) + ".png")).string());
        expectSFImagesEqual(edge,
                            imageBinaryToSFImage(rearrangement.dualEdges.slice(e)),
                            "incorrect edge " + std::to_string(e));
    }
}
