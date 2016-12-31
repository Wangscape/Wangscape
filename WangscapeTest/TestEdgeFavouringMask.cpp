#include <gtest/gtest.h>
#include <noise/module/NormLPQ.h>
#include <noise/module/ModuleFactories.h>

class TestEdgeFavouringMask : public ::testing::Test {
protected:
    noise::Reseedable n1_1;
    noise::Reseedable n1_2;

    noise::Reseedable n2_1;
    noise::Reseedable n2_2;

    noise::Reseedable n05_1;
    noise::Reseedable n05_05;

    noise::Reseedable n2_1_05;

    TestEdgeFavouringMask() :
        n1_1(noise::module::makeEdgeFavouringMask(1)),
        n1_2(noise::module::makeEdgeFavouringMask(1, 2)),
        n2_1(noise::module::makeEdgeFavouringMask(2, 1)),
        n2_2(noise::module::makeEdgeFavouringMask(2, 2)),
        n05_1(noise::module::makeEdgeFavouringMask(0.5, 1)),
        n05_05(noise::module::makeEdgeFavouringMask(0.5, 0.5)),
        n2_1_05(noise::module::makeEdgeFavouringMask(2, 1, 0.5))
    {

    };
    ~TestEdgeFavouringMask() {};
};

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_1)
{
    EXPECT_EQ(-1., n1_1.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_1.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_1.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n1_1.getValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_2)
{
    EXPECT_EQ(-1., n1_2.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_2.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_2.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(1., n1_2.getValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_1)
{
    EXPECT_EQ(-1., n2_1.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_1.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(2.*sqrt(0.5) - 1., n2_1.getValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_2)
{
    EXPECT_EQ(-1., n2_2.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_2.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_2.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.0, n2_2.getValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_1)
{
    EXPECT_EQ(-1., n05_1.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_1.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_1.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_1.getValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_05)
{
    EXPECT_EQ(-1., n05_05.getValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_05.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_05.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_05.getValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_1_05)
{
    EXPECT_NEAR(0.5, n2_1_05.getValue(0.5, 0.5, 0.5), 0.0001) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_1_05.getValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.getValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.getValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.getValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1_05.getValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.getValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.getValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.getValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.5 + sqrt(0.125), n2_1_05.getValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}