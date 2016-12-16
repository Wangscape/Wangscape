#include <gtest/gtest.h>
#include <NormLPQ.h>
#include <ModuleFactories.h>

class TestEdgeFavouringMask : public ::testing::Test {
protected:
    Reseedable n1_1;
    Reseedable n1_2;

    Reseedable n2_1;
    Reseedable n2_2;

    Reseedable n05_1;
    Reseedable n05_05;

    Reseedable n2_1_05;

    TestEdgeFavouringMask() :
        n1_1(makeEdgeFavouringMask(1)),
        n1_2(makeEdgeFavouringMask(1, 2)),
        n2_1(makeEdgeFavouringMask(2, 1)),
        n2_2(makeEdgeFavouringMask(2, 2)),
        n05_1(makeEdgeFavouringMask(0.5, 1)),
        n05_05(makeEdgeFavouringMask(0.5, 0.5)),
        n2_1_05(makeEdgeFavouringMask(2, 1, 0.5))
    {

    };
    ~TestEdgeFavouringMask() {};
};

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_1)
{
    EXPECT_EQ(-1., n1_1.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_1.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_1.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n1_1.module->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_2)
{
    EXPECT_EQ(-1., n1_2.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_2.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_2.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(1., n1_2.module->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_1)
{
    EXPECT_EQ(-1., n2_1.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_1.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(2.*sqrt(0.5) - 1., n2_1.module->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_2)
{
    EXPECT_EQ(-1., n2_2.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_2.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_2.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.0, n2_2.module->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_1)
{
    EXPECT_EQ(-1., n05_1.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_1.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_1.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_1.module->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_05)
{
    EXPECT_EQ(-1., n05_05.module->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_05.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_05.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_05.module->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_1_05)
{
    EXPECT_NEAR(0.5, n2_1_05.module->GetValue(0.5, 0.5, 0.5), 0.0001) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_1_05.module->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.module->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.module->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1_05.module->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1_05.module->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.module->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.module->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1_05.module->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.5 + sqrt(0.125), n2_1_05.module->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}