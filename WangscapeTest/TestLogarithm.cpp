#include <gtest/gtest.h>
#include <noise/module/Logarithm.h>
#include <noise/module/Gradient.h>
#include <memory>

class TestLogarithm: public ::testing::Test
{
protected:
    TestLogarithm() = default;
    noise::module::Logarithm logarithm;
    noise::module::GradientX x;
    noise::module::GradientY y;
    noise::module::GradientZ z;
};

TEST_F(TestLogarithm, TestLogarithmBase2)
{
    EXPECT_EQ(2, logarithm.GetBase()) << "Default logarithm base incorrect";
    logarithm.SetSourceModule(0, x);
    EXPECT_NEAR(1., logarithm.GetValue(2.,10.,-100.), 0.0001) <<
        "Incorrect value";
    logarithm.SetBase(2);
    logarithm.SetSourceModule(0, y);
    EXPECT_NEAR(-2., logarithm.GetValue(-1000, 0.25, -100.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestLogarithm, TestLogarithmBase10)
{
    logarithm.SetBase(10.);
    EXPECT_EQ(10., logarithm.GetBase()) << "Logarithm base not set";
    logarithm.SetSourceModule(0, y);
    EXPECT_NEAR(2., logarithm.GetValue(298347., 100., -100.), 0.0001) <<
        "Incorrect value";
    logarithm.SetSourceModule(0, z);
    EXPECT_NEAR(-3., logarithm.GetValue(-1000, 0.25, 0.001), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestLogarithm, TestLogarithm0)
{
    logarithm.SetSourceModule(0, x);
    EXPECT_NO_THROW({ logarithm.GetValue(0., 1., 1.); });
    logarithm.SetBase(10.);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), logarithm.GetValue(0., 1., 1.));
}

TEST_F(TestLogarithm, TestLogarithmNegative)
{
    logarithm.SetSourceModule(0, x);
    EXPECT_NO_THROW({logarithm.GetValue(-1., 1., 1.);});
    logarithm.SetBase(10.);
    EXPECT_TRUE(std::isnan(logarithm.GetValue(-1., 1., 1.)));
}