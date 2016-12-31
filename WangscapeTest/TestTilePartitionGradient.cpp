#include <gtest/gtest.h>

#include <TilePartitionGradient.h>
#include <Options.h>
#include <OptionsManager.h>

class TestTilePartitionGradient: public ::testing::Test{
protected:
    std::string filename;
    const Options& options;
    const OptionsManager optionsManager;
    TilePartition tp;

    TestTilePartitionGradient() :
        filename("../Wangscape/example/example_options.json"),
        optionsManager(filename),
        options(optionsManager.getOptions())
    {
        tile_partition_gradient(tp,{ "g","g","s","s" }, options);
    };
    ~TestTilePartitionGradient() {};
};

 
TEST_F(TestTilePartitionGradient, TestGradientWeight)
{
    // Doesn't use the test fixture - move to a different test case?
    EXPECT_EQ(31, gradient_weight(0, 0, 0, 0, 31));
    EXPECT_EQ(0, gradient_weight(0, 0, 31, 0, 31));
    EXPECT_EQ(0, gradient_weight(0, 0, 0, 31, 31));
    EXPECT_EQ(0, gradient_weight(0, 0, 31, 31, 31));
}

TEST_F(TestTilePartitionGradient, TestGradientPartition)
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

