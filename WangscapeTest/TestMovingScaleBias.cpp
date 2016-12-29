#include <gtest/gtest.h>

#include <ModuleFactories.h>

class TestMovingScaleBias : public ::testing::Test {
protected:
    Reseedable x;
    Reseedable y;
    Reseedable msb;
    Reseedable lmsb1;
    Reseedable lmsb2;

    TestMovingScaleBias() :
        x(makeX()),
        y(makeY()),
        msb(makeMovingScaleBias(x, (y * 2) + 1, (y * 3) + 2)),
        // these need updating for 2D lmsbs!
        lmsb1(makeLinearMovingScaleBias(y, true,true)),
        lmsb2(makeLinearMovingScaleBias(x, false, false, 0.5, 0.25))
    {

    };
    ~TestMovingScaleBias() {};
};

TEST_F(TestMovingScaleBias, TestMovingScaleBias)
{
    EXPECT_NEAR(1.5, msb.getValue(0., 0., 3453.), 0.0001);
    EXPECT_NEAR(3., msb.getValue(-1., 1., 3453.), 0.0001);
    EXPECT_NEAR(-1., msb.getValue(345304895., -1., 3453.), 0.0001);
    EXPECT_NEAR(8., msb.getValue(1., 2., 3453.), 0.0001);
}

TEST_F(TestMovingScaleBias, TestLinearMovingScaleBiasDefault)
{
    EXPECT_NEAR(1., lmsb1.getValue(0., 2598., 3453.), 0.0001);
    EXPECT_NEAR(1., lmsb1.getValue(0.5, 1., 3453.), 0.0001);
    EXPECT_NEAR(0.25, lmsb1.getValue(-0.5, -0.5, 3453.), 0.0001);
    EXPECT_NEAR(0., lmsb1.getValue(1., 2564., 3453.), 0.0001);
    EXPECT_NEAR(0., lmsb1.getValue(-1., 572., 3453.), 0.0001);
}

TEST_F(TestMovingScaleBias, TestLinearMovingScaleBiasShort)
{
    EXPECT_NEAR(1., lmsb2.getValue(-26564., 0., 3453.), 0.0001);
    EXPECT_NEAR(0.5, lmsb2.getValue(0., 0.125, 3453.), 0.0001);
    EXPECT_NEAR(1., lmsb2.getValue(1., -0.25, 3453.), 0.0001);
    EXPECT_NEAR(0.75, lmsb2.getValue(0.5, 0.375, 3453.), 0.0001);
    EXPECT_NEAR(0., lmsb2.getValue(3740., -0.5, 3453.), 0.0001);
    EXPECT_NEAR(0., lmsb2.getValue(-253., -1., 3453.), 0.0001);
}

TEST_F(TestMovingScaleBias, TestLinearMovingScaleBiasComponents)
{
    double length = 0.5;
    double middle_length = 0.25;
    double slope_length = (length - middle_length) / 2.;
    double slope = 1. / slope_length;
    double intercept = length*slope;
    Reseedable z = makeX();
    Reseedable peak = z.abs()*(-slope);
    ASSERT_EQ(0, peak.getValue(0, 0, 0));
    ASSERT_EQ(-8, peak.getValue(1, 0, 0));
    ASSERT_EQ(-16, peak.getValue(-2, 0, 0));
    ASSERT_EQ(-24, peak.getValue(3, 0, 0));
    ASSERT_EQ(-32, peak.getValue(-4, 0, 0));
    Reseedable min = (peak + 1).clamp(0, 1);
    EXPECT_NEAR(1., min.getValue(0., -26564., 3453.), 0.0001);
    EXPECT_NEAR(0., min.getValue(0.125, 0., 3453.), 0.0001);
    EXPECT_NEAR(0., min.getValue(-0.25, 1., 3453.), 0.0001);
    EXPECT_NEAR(0., min.getValue(0.375, 0.5, 3453.), 0.0001);
    EXPECT_NEAR(0., min.getValue(-0.5, 3740., 3453.), 0.0001);
    EXPECT_NEAR(0., min.getValue(-1., -253., 3453.), 0.0001);
    Reseedable max = (peak + intercept).clamp(0, 1);
    EXPECT_NEAR(1., max.getValue(0., -26564., 3453.), 0.0001);
    EXPECT_NEAR(1., max.getValue(0.125, 0., 3453.), 0.0001);
    EXPECT_NEAR(1., max.getValue(-0.25, 1., 3453.), 0.0001);
    EXPECT_NEAR(1., max.getValue(0.375, 0.5, 3453.), 0.0001);
    EXPECT_NEAR(0., max.getValue(-0.5, 3740., 3453.), 0.0001);
    EXPECT_NEAR(0., max.getValue(-1., -253., 3453.), 0.0001);
}
