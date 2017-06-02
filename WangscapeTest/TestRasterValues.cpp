#include <gtest/gtest.h>

#include <noise/RasterValues.h>
#include <noise/module/WangscapeModules.h>

class TestRasterValues : public ::testing::Test
{
protected:
    noise::module::GradientX gradientXModule;
    noise::module::GradientY gradientYModule;
    noise::module::Const constModule;
    TestRasterValues()
    {
        constModule.SetConstValue(10.);
    };
};

TEST_F(TestRasterValues, TestRasterValuesConstructors)
{
    noise::RasterValues<double> rv1(10,20);
    EXPECT_EQ(10, rv1.sizeX());
    EXPECT_EQ(20, rv1.sizeY());

    noise::RasterValues<double> rv2(20, 10, {-1., -2., 3., 4.});
    EXPECT_EQ(20, rv2.sizeX());
    EXPECT_EQ(10, rv2.sizeY());
    EXPECT_EQ(-1., rv2.bounds().left);
    EXPECT_EQ(-2., rv2.bounds().top);
    EXPECT_EQ(3., rv2.bounds().width);
    EXPECT_EQ(4., rv2.bounds().height);

    noise::RasterValues<double> rv3(5, 5, {0, 0, 1, 1}, constModule);
    EXPECT_EQ(5, rv3.sizeX());
    EXPECT_EQ(5, rv3.sizeY());
    EXPECT_EQ(0., rv3.bounds().left);
    EXPECT_EQ(0., rv3.bounds().top);
    EXPECT_EQ(1., rv3.bounds().width);
    EXPECT_EQ(1., rv3.bounds().height);
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 5; y++)
        {
            EXPECT_EQ(10., rv3.get(x, y));
        }
    }
}

TEST_F(TestRasterValues, TestRasterValuesOutOfRange)
{
    noise::RasterValues<double> rv(10, 10);

    EXPECT_ANY_THROW(rv.get(-1, -1););
    EXPECT_ANY_THROW(rv.get(0, -1););
    EXPECT_ANY_THROW(rv.get(9, -1););
    EXPECT_ANY_THROW(rv.get(10, -1););

    EXPECT_ANY_THROW(rv.get(-1, 0););
    EXPECT_ANY_THROW(rv.get(10, 0););

    EXPECT_ANY_THROW(rv.get(-1, 9););
    EXPECT_ANY_THROW(rv.get(10, 9););

    EXPECT_ANY_THROW(rv.get(-1, 10););
    EXPECT_ANY_THROW(rv.get(0, 10););
    EXPECT_ANY_THROW(rv.get(9, 10););
    EXPECT_ANY_THROW(rv.get(10, 10););
}

TEST_F(TestRasterValues, TestRasterValuesBuild)
{
    noise::RasterValues<double> rv(10, 10, {-1, -1, 2, 2});
    rv.build(gradientXModule);
    EXPECT_NEAR(-0.9, rv.get(0, 0), 0.0001);
    EXPECT_NEAR(-0.9, rv.get(0, 9), 0.0001);
    EXPECT_NEAR(0.9, rv.get(9, 0), 0.0001);
    EXPECT_NEAR(0.9, rv.get(9, 9), 0.0001);
    rv.build(gradientYModule);
    EXPECT_NEAR(-0.9, rv.get(0, 0), 0.0001);
    EXPECT_NEAR(-0.9, rv.get(9, 0), 0.0001);
    EXPECT_NEAR(0.9, rv.get(0, 9), 0.0001);
    EXPECT_NEAR(0.9, rv.get(9, 9), 0.0001);

}