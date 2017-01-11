#include <gtest/gtest.h>

#include <tilegen/partition/TilePartitionerGradient.h>
#include <Options.h>
#include <OptionsManager.h>

#include "TestRequiringOptions.h"

class TestTilePartitionerGradient : public TestRequiringOptions
{
protected:
    tilegen::partition::TilePartitionerGradient tpg;
    tilegen::partition::TilePartitionerGradient::TilePartition tp;
    TestTilePartitionerGradient() :
        TestRequiringOptions(),
        tpg(options)
    {
    };
    ~TestTilePartitionerGradient() {};
};

 
TEST_F(TestTilePartitionerGradient, TestGradientWeight)
{
    EXPECT_LT(0, tpg.gradientWeight(0, 0, 0, 0, 8));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 31, 0, 8));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 0, 31, 8));
    EXPECT_EQ(0, tpg.gradientWeight(0, 0, 31, 31, 8));
}

TEST_F(TestTilePartitionerGradient, TestGradientPartition)
{
    tilegen::partition::TilePartitionerGradient::TilePartition tp;
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

