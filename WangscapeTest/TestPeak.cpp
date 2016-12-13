#include <gtest/gtest.h>

#include <ModuleFactories.h>

class TestPeak : public ::testing::Test {
protected:
    ModulePtr px;
    ModulePtr py;

    TestPeak() :
        px(makePeak(true)),
        py(makePeak(false))
    {

    };
    ~TestPeak() {};
};

TEST_F(TestPeak, TestPeakX)
{
    EXPECT_EQ(1., px->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";
    EXPECT_EQ(1., px->GetValue(0., 235.1, 92.7)) <<
        "Incorrect value at peak";
    EXPECT_EQ(-3., px->GetValue(-4., 0., 0.)) <<
        "Incorrect value";
    EXPECT_NEAR(-633.9, px->GetValue(634.9, 235.1, 92.7), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestPeak, TestPeakY)
{
    EXPECT_EQ(1., py->GetValue(0., 0., 0.)) <<
        "Incorrect value at origin";
    EXPECT_EQ(1., py->GetValue(235.1, 0., 92.7)) <<
        "Incorrect value at peak";
    EXPECT_EQ(-3., py->GetValue(0., -4., 0.)) <<
        "Incorrect value";
    EXPECT_NEAR(-633.9, py->GetValue(235.1, 634.9, 92.7), 0.0001) <<
        "Incorrect value";
}
