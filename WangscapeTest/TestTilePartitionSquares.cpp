#include <gtest/gtest.h>
#include <TilePartitionSquares.h>

#include <Options.h>
#include <OptionsManager.h>

class TestTilePartitionSquares : public ::testing::Test {
protected:
    std::string filename;
    const Options& options;
    const OptionsManager optionsManager;
    TilePartition tp;

    TestTilePartitionSquares() :
        filename("../Wangscape/example/example_options.json"),
        optionsManager(filename),
        options(optionsManager.getOptions())
    {
        tile_partition_squares(tp, { "g","g","s","s" }, options);
    };
    ~TestTilePartitionSquares() {};
};

TEST_F(TestTilePartitionSquares, TestSquarePartition)
{
    sf::Image mask = tp[0].first.copyToImage();
    EXPECT_EQ(mask.getPixel(0, 0), sf::Color(255, 255, 255, 255)) <<
        "Mask 0: Wrong colour in top left pixel";
    EXPECT_EQ(mask.getPixel(0, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 0: Wrong colour in bottom left pixel";
    EXPECT_EQ(mask.getPixel(31, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 0: Wrong colour in top right pixel";
    EXPECT_EQ(mask.getPixel(31, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 0: Wrong colour in bottom right pixel";

    mask = tp[1].first.copyToImage();
    EXPECT_EQ(mask.getPixel(0, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 1: Wrong colour in top left pixel";
    EXPECT_EQ(mask.getPixel(0, 31), sf::Color(255, 255, 255, 255)) <<
        "Mask 1: Wrong colour in bottom left pixel";
    EXPECT_EQ(mask.getPixel(31, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 1: Wrong colour in top right pixel";
    EXPECT_EQ(mask.getPixel(31, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 1: Wrong colour in bottom right pixel";

    mask = tp[2].first.copyToImage();
    EXPECT_EQ(mask.getPixel(0, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 2: Wrong colour in top left pixel";
    EXPECT_EQ(mask.getPixel(0, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 2: Wrong colour in bottom left pixel";
    EXPECT_EQ(mask.getPixel(31, 0), sf::Color(255, 255, 255, 255)) <<
        "Mask 2: Wrong colour in top right pixel";
    EXPECT_EQ(mask.getPixel(31, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 2: Wrong colour in bottom right pixel";

    mask = tp[3].first.copyToImage();
    EXPECT_EQ(mask.getPixel(0, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 3: Wrong colour in top left pixel";
    EXPECT_EQ(mask.getPixel(0, 31), sf::Color(255, 255, 255, 0)) <<
        "Mask 3: Wrong colour in bottom left pixel";
    EXPECT_EQ(mask.getPixel(31, 0), sf::Color(255, 255, 255, 0)) <<
        "Mask 3: Wrong colour in top right pixel";
    EXPECT_EQ(mask.getPixel(31, 31), sf::Color(255, 255, 255, 255)) <<
        "Mask 3: Wrong colour in bottom right pixel";
}
