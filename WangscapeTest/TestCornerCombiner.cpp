#include <gtest/gtest.h>

#include <CornerCombiner.h>
#include <CornerCombinerGroup.h>

class TestCornerCombiner : public ::testing::Test {
protected:
    CornerCombiner cc1;
    CornerCombiner cc05;
    CornerCombiner cc2;
    CornerCombinerGroup ccg2;
    TestCornerCombiner():
        cc1(), cc05(0.5), cc2(2.), ccg2(2.)
    {

    };
    ~TestCornerCombiner() {};
};

TEST_F(TestCornerCombiner, TestCornerCombinerPowers)
{
    EXPECT_EQ(0.5, cc05.power) << "Power not correctly assigned";
    EXPECT_EQ(1., cc1.power) << "Power not correctly assigned";
    EXPECT_EQ(2., cc2.power) << "Power not correctly assigned";
}

TEST_F(TestCornerCombiner, TestCornerCombiner1)
{
    EXPECT_EQ(0., cc1.GetValue(0., 0., 0.0001)) <<
        "Incorrect value at (0,0) with power 1";
    EXPECT_EQ(0., cc1.GetValue(0.5, 0.5, 0.0001)) <<
        "Incorrect value at (0.5,0.5) with power 1";
    EXPECT_EQ(0., cc1.GetValue(1., 1. , 0.0001)) <<
        "Incorrect value at (1,1) with power 1";

    EXPECT_NEAR(1., cc1.GetValue(0.5, 0., 0.0001), 0.001) <<
        "Incorrect value at (0.5,0) with power 1";
    EXPECT_NEAR(1., cc1.GetValue(1., 0., 0.0001), 0.001) <<
        "Incorrect value at (1,0) with power 1";

    EXPECT_NEAR(-1., cc1.GetValue(0., 0.5, 0.0001), 0.001) <<
        "Incorrect value at (0,0.5) with power 1";
    EXPECT_NEAR(-1., cc1.GetValue(0., 1., 0.0001), 0.001) <<
        "Incorrect value at (0,1) with power 1";
}

TEST_F(TestCornerCombiner, TestCornerCombiner05)
{
    EXPECT_EQ(0., cc05.GetValue(0., 0., 0.0001)) <<
        "Incorrect value at (0,0) with power 0.5";
    EXPECT_EQ(0., cc05.GetValue(0.5, 0.5, 0.0001)) <<
        "Incorrect value at (0.5,0.5) with power 0.5";
    EXPECT_EQ(0., cc05.GetValue(1., 1., 0.0001)) <<
        "Incorrect value at (1,1) with power 0.5";

    EXPECT_LT(0.5, cc05.GetValue(0.5, 0., 0.0001)) <<
        "Incorrect value at (0.5,0) with power 0.5";
    EXPECT_NEAR(1.0, cc05.GetValue(1., 0., 0.0001), 0.001) <<
        "Incorrect value at (1,0) with power 0.5";

    EXPECT_GT(-0.5, cc05.GetValue(0., 0.5, 0.0001)) <<
        "Incorrect value at (0,0.5) with power 0.5";
    EXPECT_NEAR(-1.0, cc05.GetValue(0., 1., 0.0001), 0.001) <<
        "Incorrect value at (0,1) with power 0.5";
}

TEST_F(TestCornerCombiner, TestCornerCombiner2)
{
    EXPECT_EQ(0., cc2.GetValue(0., 0., 0.0001)) <<
        "Incorrect value at (0,0) with power 2";
    EXPECT_EQ(0., cc2.GetValue(0.5, 0.5, 0.0001)) <<
        "Incorrect value at (0.5,0.5) with power 2";
    EXPECT_EQ(0., cc2.GetValue(1., 1., 0.0001)) <<
        "Incorrect value at (1,1) with power 2";

    EXPECT_LT(1., cc2.GetValue(0.5, 0., 0.0001)) <<
        "Incorrect value at (0.5,0) with power 2";
    EXPECT_NEAR(1., cc2.GetValue(1., 0., 0.0001), 0.001) <<
        "Incorrect value at (1,0) with power 2";

    EXPECT_GT(-1., cc2.GetValue(0., 0.5, 0.0001)) <<
        "Incorrect value at (0,0.5) with power 2";
    EXPECT_NEAR(-1., cc2.GetValue(0., 1., 0.0001), 0.001) <<
        "Incorrect value at (0,1) with power 2";
}

TEST_F(TestCornerCombiner, TestCornerCombinerGroup2)
{
    EXPECT_NEAR(0.5, ccg2.getOutput().GetValue(0., 0., 0.0001), 0.00001) <<
        "Incorrect clamped value at (0,0) with power 2";
    EXPECT_NEAR(0.5, ccg2.getOutput().GetValue(0.5, 0.5, 0.0001), 0.0000) <<
        "Incorrect clamped value at (0.5,0.5) with power 2";
    EXPECT_NEAR(0.5, ccg2.getOutput().GetValue(1., 1., 0.0001), 0.0000) <<
        "Incorrect clamped value at (1,1) with power 2";

    EXPECT_EQ(1., ccg2.getOutput().GetValue(0.5, 0., 0.0001)) <<
        "Incorrect clamped value at (0.5,0) with power 2";
    EXPECT_NEAR(1., ccg2.getOutput().GetValue(1., 0., 0.0001), 0.001) <<
        "Incorrect clamped value at (1,0) with power 2";

    EXPECT_EQ(0., ccg2.getOutput().GetValue(0., 0.5, 0.0001)) <<
        "Incorrect clamped value at (0,0.5) with power 2";
    EXPECT_NEAR(0., ccg2.getOutput().GetValue(0., 1., 0.0001), 0.001) <<
        "Incorrect clamped value at (0,1) with power 2";
}
