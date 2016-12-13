#include <gtest/gtest.h>
#include <NormLPQ.h>
#include <ModuleFactories.h>

class TestEdgeFavouringMask : public ::testing::Test {
protected:
    ModulePtr n1_1;
    ModulePtr n1_2;

    ModulePtr n2_1;
    ModulePtr n2_2;

    ModulePtr n05_1;
    ModulePtr n05_05;

    TestEdgeFavouringMask() :
        n1_1(makeEdgeFavouringMask(1)),
        n1_2(makeEdgeFavouringMask(1, 2)),
        n2_1(makeEdgeFavouringMask(2, 1)),
        n2_2(makeEdgeFavouringMask(2, 2)),
        n05_1(makeEdgeFavouringMask(0.5, 1)),
        n05_05(makeEdgeFavouringMask(0.5, 0.5))
    {

    };
    ~TestEdgeFavouringMask() {};
};

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_1)
{
    EXPECT_EQ(0., n1_1->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_1->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n1_1->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask1_2)
{
    EXPECT_EQ(0., n1_2->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n1_2->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n1_2->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_2->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(1., n1_2->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_1)
{
    EXPECT_EQ(0., n2_1->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(sqrt(0.5), n2_1->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask2_2)
{
    EXPECT_EQ(0., n2_2->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n2_2->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n2_2->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_2->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.5, n2_2->GetValue(0.75, 0.75, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_1)
{
    EXPECT_EQ(0., n05_1->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_1->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_1->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}

TEST_F(TestEdgeFavouringMask, TestEdgeFavouringMask05_05)
{
    EXPECT_EQ(0., n05_05->GetValue(0.5, 0.5, 0.5)) <<
        "Incorrect value at origin";

    EXPECT_EQ(1., n05_05->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05->GetValue(0., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05->GetValue(1., 0., 0.)) <<
        "Incorrect value at corner";
    EXPECT_EQ(1., n05_05->GetValue(0., 0., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_05->GetValue(1., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0., 0.5, 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0.5, 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0.5, 0., 0.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n05_05->GetValue(0.75, 0.75, 0.)) <<
        "Incorrect value";
}