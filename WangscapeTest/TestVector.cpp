#include <gtest/gtest.h>
#include <Vector.h>

class TestVector: public ::testing::Test
{
protected:
    IVec iv{0, 1};
    UVec uv{2, 3};
    DVec dv{4, 5};

    IVec iv2{6, 7};
    UVec uv2{8, 9};
    DVec dv2{10, 11};
};

TEST_F(TestVector, TestVectorFields)
{
    EXPECT_EQ(0, iv.x());
    EXPECT_EQ(1, iv.y());
    EXPECT_EQ(2, uv.x());
    EXPECT_EQ(3, uv.y());
    EXPECT_EQ(4, dv.x());
    EXPECT_EQ(5, dv.y());
}

TEST_F(TestVector, TestVectorVectorOps)
{
    EXPECT_EQ(IVec(6, 8), iv + iv2);
    EXPECT_EQ(UVec(10, 12), uv + uv2);
    EXPECT_EQ(DVec(14, 16), dv + dv2);

    EXPECT_EQ(IVec(-6, -6), iv - iv2);

    EXPECT_EQ(UVec(16, 27), uv*uv2);

    EXPECT_EQ(DVec(2.5, 2.2), dv2 / dv);

    EXPECT_EQ(iv, iv);

    EXPECT_NE(uv, uv2);
}

TEST_F(TestVector, TestVectorScalarOps)
{
    EXPECT_EQ(IVec(1, 2), iv + 1);
    EXPECT_EQ(UVec(4, 5), uv + 2u);
    EXPECT_EQ(DVec(7, 8), dv + 3.);

    EXPECT_EQ(IVec(2, 3), iv2 - 4);

    EXPECT_EQ(UVec(10, 15), uv * 5);

    EXPECT_EQ(DVec(2.5, 2.75), dv2 / 4);
}

TEST_F(TestVector, TestVectorConversions)
{
    EXPECT_EQ(IVec(2, 3), IVec(uv));
    EXPECT_EQ(DVec(6, 7), DVec(iv2));
}
