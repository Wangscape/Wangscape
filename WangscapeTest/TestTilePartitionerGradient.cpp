#include <gtest/gtest.h>

#include <TilePartitionerGradient.h>
#include <Options.h>

class TestTilePartitionerGradient : public ::testing::Test{
protected:
    std::string filename;
    const Options options;
    TilePartitionerGradient tpg;


    TestTilePartitionerGradient() :
        filename("../Wangscape/example/example_options.json"),
        options(filename),
        tpg(options)
    {
    };
    ~TestTilePartitionerGradient() {};
};

 
TEST_F(TestTilePartitionerGradient, TestGradientWeight)
{
    // Doesn't use the test fixture - move to a different test case?
    EXPECT_EQ(31, tpg.gradientWeight(0, 0, 0, 0, 31));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 31, 0, 31));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 0, 31, 31));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 31, 31, 31));
}

TEST_F(TestTilePartitionerGradient, TestGradientPartition)
{
    TilePartitionerGradient::TilePartition tp;
    tpg.makePartition(tp, { "g","g","s","s" });
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

