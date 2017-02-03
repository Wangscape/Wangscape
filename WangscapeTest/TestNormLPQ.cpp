#include <gtest/gtest.h>
#include <noise/module/NormLPQ.h>
#include <noise/module/ReseedableOps.h>

class TestNormLPQ : public ::testing::Test
{
protected:
    std::shared_ptr<noise::module::NormLPQ> n1_1;
    std::shared_ptr<noise::module::NormLPQ> n1_2;

    std::shared_ptr<noise::module::NormLPQ> n2_1;
    std::shared_ptr<noise::module::NormLPQ> n2_2;

    std::shared_ptr<noise::module::NormLPQ> n05_1;
    std::shared_ptr<noise::module::NormLPQ> n05_05;

    TestNormLPQ() :
        n1_1(std::make_shared<noise::module::NormLPQ>()),
        n1_2(std::make_shared<noise::module::NormLPQ>()),
        n2_1(std::make_shared<noise::module::NormLPQ>()),
        n2_2(std::make_shared<noise::module::NormLPQ>()),
        n05_1(std::make_shared<noise::module::NormLPQ>()),
        n05_05(std::make_shared<noise::module::NormLPQ>())
    {
        n1_1->setPQ(1);
        n1_2->setPQ(1, 2);
        n2_1->setPQ(2, 1);
        n2_2->setPQ(2, 2);
        n05_1->setPQ(0.5, 1);
        n05_05->setPQ(0.5, 0.5);
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