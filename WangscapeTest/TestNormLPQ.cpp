#include <gtest/gtest.h>
#include <NormLPQ.h>
#include <ModuleFactories.h>

class TestNormLPQ : public ::testing::Test {
protected:
    ModulePtr n1_1;
    ModulePtr n1_2;

    ModulePtr n2_1;
    ModulePtr n2_2;

    ModulePtr n05_1;
    ModulePtr n05_05;

    TestNormLPQ() :
        n1_1(std::make_shared<NormLPQ>(1)),
        n1_2(std::make_shared<NormLPQ>(1, 2)),
        n2_1(std::make_shared<NormLPQ>(2, 1)),
        n2_2(std::make_shared<NormLPQ>(2, 2)),
        n05_1(std::make_shared<NormLPQ>(0.5, 1)),
        n05_05(std::make_shared<NormLPQ>(0.5, 0.5))
    {

    };
    ~TestNormLPQ() {};
};

TEST_F(TestNormLPQ, TestNormLPQ1_1)
{
    EXPECT_EQ(0., n1_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n1_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_1->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_1->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_1->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_1->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_1->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_EQ(1., n1_1->GetValue(0.5, 0.5, 0.)) <<
        "Incorrect value";
}

TEST_F(TestNormLPQ, TestNormLPQ1_2)
{
    EXPECT_EQ(0., n1_2->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n1_2->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_2->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_2->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n1_2->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n1_2->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n1_2->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(1., n1_2->GetValue(0.5, 0.5, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestNormLPQ, TestNormLPQ2_1)
{
    EXPECT_EQ(0., n2_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n2_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_1->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_1->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_1->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_1->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_1->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(sqrt(0.5), n2_1->GetValue(0.5, 0.5, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestNormLPQ, TestNormLPQ2_2)
{
    EXPECT_EQ(0., n2_2->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n2_2->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_2->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_2->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n2_2->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n2_2->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n2_2->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(0.5, n2_2->GetValue(0.5, 0.5, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestNormLPQ, TestNormLPQ05_1)
{
    EXPECT_EQ(0., n05_1->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n05_1->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_1->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_1->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_1->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_1->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_1->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(2., n05_1->GetValue(0.5, 0.5, 0.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestNormLPQ, TestNormLPQ05_05)
{
    EXPECT_EQ(0., n05_05->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";

    EXPECT_LT(1., n05_05->GetValue(1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_05->GetValue(-1., 1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_05->GetValue(1., -1., 0.)) <<
        "Incorrect value at corner";
    EXPECT_LT(1., n05_05->GetValue(-1., -1., 0.)) <<
        "Incorrect value at corner";

    EXPECT_EQ(1., n05_05->GetValue(1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(-1., 0., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0., 1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0., -1., 0.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0., 0., 1.)) <<
        "Incorrect value on axis";
    EXPECT_EQ(1., n05_05->GetValue(0., 0., -1.)) <<
        "Incorrect value on axis";

    EXPECT_NEAR(sqrt(2.), n05_05->GetValue(0.5, 0.5, 0.), 0.0001) <<
        "Incorrect value";
}