#include <gtest/gtest.h>
#include <noise/module/Reciprocal.h>
#include <noise/module/Gradient.h>
#include <memory>

class TestReciprocal : public ::testing::Test
{
protected:
    TestReciprocal() = default;
    noise::module::Reciprocal reciprocal;
    noise::module::GradientX x;
    noise::module::GradientY y;
    noise::module::GradientZ z;
};

TEST_F(TestReciprocal, TestReciprocalFinite)
{
    reciprocal.SetSourceModule(0, x);
    EXPECT_NEAR(0.5, reciprocal.GetValue(2., 10., -100.), 0.0001) <<
        "Incorrect value";
    reciprocal.SetSourceModule(0, y);
    EXPECT_NEAR(-4., reciprocal.GetValue(-1000, -0.25, -100.), 0.0001) <<
        "Incorrect value";
    reciprocal.SetSourceModule(0, z);
    EXPECT_NEAR(-0.01, reciprocal.GetValue(-239847, 3833, -100.), 0.0001) <<
        "Incorrect value";
}

TEST_F(TestReciprocal, TestReciprocalInfinite)
{
    reciprocal.SetSourceModule(0, x);
    EXPECT_NO_THROW({reciprocal.GetValue(0., 1., 1.);});
    EXPECT_EQ(std::numeric_limits<double>::infinity(), reciprocal.GetValue(0., 1., 1.));

    EXPECT_NO_THROW({reciprocal.GetValue(std::numeric_limits<double>::infinity(), 1., 1.); });
    EXPECT_EQ(0., reciprocal.GetValue(std::numeric_limits<double>::infinity(), 1., 1.));
}
