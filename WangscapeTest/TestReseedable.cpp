#include <gtest/gtest.h>

#include <noise/MakeReseedable.h>
#include <noise/module/ModuleFactories.h>

class TestReseedable : public ::testing::Test {
protected:
    noise::Reseedable x;
    noise::Reseedable y;
    noise::Reseedable c05;
    TestReseedable() :
        x(noise::module::makeX()),
        y(noise::module::makeY()),
        c05(noise::makeReseedable(std::make_shared<noise::module::Const>()))
    {
        ((noise::module::Const&)(*c05.module)).SetConstValue(0.5);
    };
    ~TestReseedable() {};
};

TEST_F(TestReseedable, TestReseedableGetValue)
{
    EXPECT_EQ(2508., x.getValue(2508., -518., 2805.)) <<
        "Incorrect value";
    EXPECT_EQ(1., y.getValue(320., 1., -39.)) <<
        "Incorrect value";
}

TEST_F(TestReseedable, TestReseedableSetSeed)
{
    EXPECT_NO_THROW({ x.setSeed(35089); });
    EXPECT_NO_THROW({ y.setSeed(293847928); });
}


TEST_F(TestReseedable, TestReseedableAbs)
{
    EXPECT_EQ(5., x.abs().getValue(-5., 0, 0));
    EXPECT_EQ(4., x.abs().getValue(4., 0, 0));
    EXPECT_EQ(3., y.abs().getValue(-5., 3., 0));
    EXPECT_EQ(2., y.abs().getValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedableClamp)
{
    EXPECT_EQ(-1., x.clamp(-1., 1.).getValue(-5., 0, 0));
    EXPECT_EQ(1., y.clamp(-1., 1.).getValue(-1., 3., 0));
    EXPECT_EQ(0., x.clamp(-5., 5.).getValue(0., 3., 0));
    EXPECT_EQ(-10., y.clamp(-10, -10).getValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedablePowDouble)
{
    EXPECT_NEAR(-8., x.pow(3).getValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(0.04, x.pow(-2).getValue(5., 0, 0));
    EXPECT_NEAR(3., y.pow(0.5).getValue(-5., 9., 0), 0.0001);
    EXPECT_EQ(1., y.pow(0).getValue(4., -2., 5.));
}

TEST_F(TestReseedable, TestReseedablePowReseedable)
{
    EXPECT_EQ(4., x.pow(x).getValue(2., 0, 0));
    EXPECT_EQ(-32., x.pow(y).getValue(-2., 5, 0));
    EXPECT_NEAR(-1953125., y.pow(x).getValue(9., -5., 0), 0.01);
    EXPECT_EQ(1. / 256., y.pow(y).getValue(4., -4., 5.));
}

TEST_F(TestReseedable, TestReseedableExpDouble)
{
    EXPECT_NEAR(1./9., x.exp(3).getValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(-32., x.exp(-2).getValue(5., 0, 0));
    EXPECT_NEAR(0.25, y.exp(0.5).getValue(-5., 2., 0), 0.0001);
    EXPECT_EQ(0., y.exp(0).getValue(4., 2., 5.));
}

TEST_F(TestReseedable, TestReseedableInv)
{
    EXPECT_EQ(16., x.invert().getValue(-16., 0, 0));
    EXPECT_EQ(-32., x.invert().getValue(32., 0, 0));
    EXPECT_EQ(3., y.invert().getValue(-5., -3., 0));
    EXPECT_EQ(-1., y.invert().getValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableScaleBias)
{
    EXPECT_EQ(-155, x.scaleBias(10, 5).getValue(-16., 0, 0));
    EXPECT_EQ(-158, x.scaleBias(-5, 2).getValue(32., 0, 0));
    EXPECT_EQ(1.5, y.scaleBias(0.5, 3).getValue(-5., -3., 0));
    EXPECT_EQ(1.5, y.scaleBias(1, 0.5).getValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddReseedable)
{
    EXPECT_EQ(74., (x + y).getValue(-16., 90., 0));
    EXPECT_EQ(64., (x + x).getValue(32., 0, 0));
    EXPECT_EQ(-8., (y + x).getValue(-5., -3., 0));
    EXPECT_EQ(2., (y + y).getValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddDouble)
{
    EXPECT_EQ(-11., (x + 5.).getValue(-16., 0, 0));
    EXPECT_EQ(-6., (y + (-3)).getValue(-5., -3., 0));
}

TEST_F(TestReseedable, TestReseedableMaxReseedable)
{
    EXPECT_EQ(-3., x.max(y).getValue(-5., -3., 0));
    EXPECT_EQ(4., y.max(x).getValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMaxDouble)
{
    EXPECT_EQ(4., x.max(4).getValue(-5., -3., 0));
    EXPECT_EQ(1., y.max(0).getValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMinReseedable)
{
    EXPECT_EQ(-5., x.min(y).getValue(-5., -3., 0));
    EXPECT_EQ(1., y.min(x).getValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMinDouble)
{
    EXPECT_EQ(-5., x.min(4).getValue(-5., -3., 0));
    EXPECT_EQ(0., y.min(0).getValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableInvert)
{
    EXPECT_EQ(-5, x.invert().getValue(5, 43, 3));
    EXPECT_EQ(4, y.invert().getValue(5, -4, 34));
}
//Reseedable curve(...?)
//Reseedable terrace(...?)
TEST_F(TestReseedable, TestReseedableSubReseedable)
{
    EXPECT_EQ(-106., (x - y).getValue(-16., 90., 0));
    EXPECT_EQ(0., (x - x).getValue(32., 0, 0));
    EXPECT_EQ(2., (y - x).getValue(-5., -3., 0));
    EXPECT_EQ(0., (y - y).getValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableSubDouble)
{
    EXPECT_EQ(-21., (x - 5.).getValue(-16., 0, 0));
    EXPECT_EQ(1., (y - (-4)).getValue(-5., -3., 0));
}
TEST_F(TestReseedable, TestReseedableSubUnary)
{
    EXPECT_EQ(-5, (-x).getValue(5, 43, 3));
    EXPECT_EQ(4, (-y).getValue(5, -4, 34));
}
TEST_F(TestReseedable, TestReseedableMulReseedable)
{
    EXPECT_EQ(-1440, (x * y).getValue(-16., 90., 0));
    EXPECT_EQ(1024., (x * x).getValue(32., 0, 0));
    EXPECT_EQ(15., (y * x).getValue(-5., -3., 0));
    EXPECT_EQ(1., (y * y).getValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMulDouble)
{
    EXPECT_EQ(-80., (x * 5.).getValue(-16., 0, 0));
    EXPECT_EQ(12., (y * (-4)).getValue(-5., -3., 0));
}
TEST_F(TestReseedable, TestReseedableBlend)
{
    EXPECT_EQ(0.75, c05.blend(x, y).getValue(0., 1., 5.));
    EXPECT_EQ(-5, (c05).blend(y, x).getValue(-1, -17, 5.));
}
TEST_F(TestReseedable, TestReseedableSelect)
{
    EXPECT_EQ(-17, c05.select(x, y).getValue(-1, -17, 5.));
    EXPECT_EQ(0., c05.select(y, x).getValue(0., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableDisplace)
{
    auto displace = (x - (y * 2)).displace(x, y, c05);
    EXPECT_EQ(0., displace.getValue(0, 0, 304958.));
    EXPECT_EQ(0., displace.getValue(2, 1, 30458.));
    EXPECT_EQ(-16., displace.getValue(-2, 3, 30458.));
}
TEST_F(TestReseedable, TestReseedableRotatePoint)
{
    EXPECT_EQ(20., x.rotatePoint(0,0,90).getValue(2, 20, 200));
    EXPECT_EQ(-30, y.rotatePoint(0,0,180).getValue(2, 30, 200));

}
TEST_F(TestReseedable, TestReseedableScalePoint)
{
    EXPECT_EQ(6., x.scalePoint(3, 30, 300).getValue(2, 20, 200));
    EXPECT_EQ(200., y.scalePoint(-1, -10, -100).getValue(2, -20, 200));

}
TEST_F(TestReseedable, TestReseedableTranslatePoint)
{
    EXPECT_EQ(3., x.translatePoint(1, 10, 100).getValue(2, 20, 200));
    EXPECT_EQ(-10., y.translatePoint(1, 10, 100).getValue(2, -20, 200));
}
TEST_F(TestReseedable, TestReseedableTurbulence)
{
    auto turbulence = c05.turbulence(2., 2., 3, 0);
    EXPECT_EQ(0.5, turbulence.getValue(346980., 0.63, 696.346));
}

TEST_F(TestReseedable, TestReseedableConst)
{
    EXPECT_EQ(3.6345, noise::module::makeConst(3.6345).getValue(52935874, 57432895, 2549));
    EXPECT_EQ(-3045.25, noise::module::makeConst(-3045.25).getValue(259, 594, 239587));
}