#include <gtest/gtest.h>
#include <noise/module/Divide.h>
#include <noise/module/Gradient.h>
#include <memory>

class TestDivide : public ::testing::Test
{
protected:
    TestDivide() = default;
    noise::module::Divide divide;
    noise::module::GradientX x;
    noise::module::GradientY y;
    noise::module::GradientZ z;
};

TEST_F(TestDivide, TestDivideFinite)
{
    divide.SetSourceModule(0, x);
    divide.SetSourceModule(1, y);

    EXPECT_NEAR(0.2, divide.GetValue(2., 10., -203948.), 0.0001) <<
        "Incorrect value";
    EXPECT_NEAR(-0.375, divide.GetValue(-3., 8., 509483.), 0.0001) <<
        "Incorrect value";

    divide.SetSourceModule(0, y);
    divide.SetSourceModule(1, z);

    EXPECT_NEAR(0.0025, divide.GetValue(-205398., -0.25, -100.), 0.000001) <<
        "Incorrect value";
    EXPECT_NEAR(5000., divide.GetValue(-239847., 50, 0.01), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestDivide, TestDivideInfinite)
{
    divide.SetSourceModule(0, x);
    divide.SetSourceModule(1, y);
    EXPECT_NO_THROW({divide.GetValue(1., 0., 1010.); });
    EXPECT_EQ(std::numeric_limits<double>::infinity(), divide.GetValue(1., 0., 1010.));

    EXPECT_NO_THROW({divide.GetValue(-1., 0., 1010.);});
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), divide.GetValue(-1., 0., 1010.));

    EXPECT_NO_THROW({divide.GetValue(0., 0., 1010.);});
    EXPECT_TRUE(std::isnan(divide.GetValue(0., 0., 1010.)));
}
