#include <gtest/gtest.h>

#include <MakeReseedable.h>
#include <ModuleFactories.h>

class TestReseedable : public ::testing::Test {
protected:
    Reseedable x;
    Reseedable y;
    Reseedable c05;
    TestReseedable() :
        x(makeX()),
        y(makeY()),
        c05(makeReseedable(std::make_shared<noise::module::Const>()))
    {
        ((noise::module::Const&)(*c05.module)).SetConstValue(0.5);
    };
    ~TestReseedable() {};
};

TEST_F(TestReseedable, TestReseedableGetValue)
{
    EXPECT_EQ(2508., x.module->GetValue(2508., -518., 2805.)) <<
        "Incorrect value";
    EXPECT_EQ(1., y.module->GetValue(320., 1., -39.)) <<
        "Incorrect value";
}

TEST_F(TestReseedable, TestReseedableSetSeed)
{
    EXPECT_NO_THROW({ x.setSeed(35089); });
    EXPECT_NO_THROW({ y.setSeed(293847928); });
}


TEST_F(TestReseedable, TestReseedableAbs)
{
    EXPECT_EQ(5., x.abs().module->GetValue(-5., 0, 0));
    EXPECT_EQ(4., x.abs().module->GetValue(4., 0, 0));
    EXPECT_EQ(3., y.abs().module->GetValue(-5., 3., 0));
    EXPECT_EQ(2., y.abs().module->GetValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedableClamp)
{
    EXPECT_EQ(-1., x.clamp(-1., 1.).module->GetValue(-5., 0, 0));
    EXPECT_EQ(1., y.clamp(-1., 1.).module->GetValue(-1., 3., 0));
    EXPECT_EQ(0., x.clamp(-5., 5.).module->GetValue(0., 3., 0));
    EXPECT_EQ(-10., y.clamp(-10, -10).module->GetValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedablePowDouble)
{
    EXPECT_NEAR(-8., x.pow(3).module->GetValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(0.04, x.pow(-2).module->GetValue(5., 0, 0));
    EXPECT_NEAR(3., y.pow(0.5).module->GetValue(-5., 9., 0), 0.0001);
    EXPECT_EQ(1., y.pow(0).module->GetValue(4., -2., 5.));
}

TEST_F(TestReseedable, TestReseedablePowReseedable)
{
    EXPECT_EQ(4., x.pow(x).module->GetValue(2., 0, 0));
    EXPECT_EQ(-32., x.pow(y).module->GetValue(-2., 5, 0));
    EXPECT_NEAR(-1953125., y.pow(x).module->GetValue(9., -5., 0), 0.01);
    EXPECT_EQ(1. / 256., y.pow(y).module->GetValue(4., -4., 5.));
}

TEST_F(TestReseedable, TestReseedableExpDouble)
{
    EXPECT_NEAR(1./9., x.exp(3).module->GetValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(-32., x.exp(-2).module->GetValue(5., 0, 0));
    EXPECT_NEAR(0.25, y.exp(0.5).module->GetValue(-5., 2., 0), 0.0001);
    EXPECT_EQ(0., y.exp(0).module->GetValue(4., 2., 5.));
}

TEST_F(TestReseedable, TestReseedableInv)
{
    EXPECT_EQ(16., x.invert().module->GetValue(-16., 0, 0));
    EXPECT_EQ(-32., x.invert().module->GetValue(32., 0, 0));
    EXPECT_EQ(3., y.invert().module->GetValue(-5., -3., 0));
    EXPECT_EQ(-1., y.invert().module->GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableScaleBias)
{
    EXPECT_EQ(-155, x.scaleBias(10, 5).module->GetValue(-16., 0, 0));
    EXPECT_EQ(-158, x.scaleBias(-5, 2).module->GetValue(32., 0, 0));
    EXPECT_EQ(1.5, y.scaleBias(0.5, 3).module->GetValue(-5., -3., 0));
    EXPECT_EQ(1.5, y.scaleBias(1, 0.5).module->GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddReseedable)
{
    EXPECT_EQ(74., (x + y).module->GetValue(-16., 90., 0));
    EXPECT_EQ(64., (x + x).module->GetValue(32., 0, 0));
    EXPECT_EQ(-8., (y + x).module->GetValue(-5., -3., 0));
    EXPECT_EQ(2., (y + y).module->GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddDouble)
{
    EXPECT_EQ(-11., (x + 5.).module->GetValue(-16., 0, 0));
    EXPECT_EQ(-6., (y + (-3)).module->GetValue(-5., -3., 0));
}

TEST_F(TestReseedable, TestReseedableMaxReseedable)
{
    EXPECT_EQ(-3., x.max(y).module->GetValue(-5., -3., 0));
    EXPECT_EQ(4., y.max(x).module->GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMaxDouble)
{
    EXPECT_EQ(4., x.max(4).module->GetValue(-5., -3., 0));
    EXPECT_EQ(1., y.max(0).module->GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMinReseedable)
{
    EXPECT_EQ(-5., x.min(y).module->GetValue(-5., -3., 0));
    EXPECT_EQ(1., y.min(x).module->GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMinDouble)
{
    EXPECT_EQ(-5., x.min(4).module->GetValue(-5., -3., 0));
    EXPECT_EQ(0., y.min(0).module->GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableInvert)
{
    EXPECT_EQ(-5, x.invert().module->GetValue(5, 43, 3));
    EXPECT_EQ(4, y.invert().module->GetValue(5, -4, 34));
}
//Reseedable curve(...?)
//Reseedable terrace(...?)
TEST_F(TestReseedable, TestReseedableSubReseedable)
{
    EXPECT_EQ(-106., (x - y).module->GetValue(-16., 90., 0));
    EXPECT_EQ(0., (x - x).module->GetValue(32., 0, 0));
    EXPECT_EQ(2., (y - x).module->GetValue(-5., -3., 0));
    EXPECT_EQ(0., (y - y).module->GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableSubDouble)
{
    EXPECT_EQ(-21., (x - 5.).module->GetValue(-16., 0, 0));
    EXPECT_EQ(1., (y - (-4)).module->GetValue(-5., -3., 0));
}
TEST_F(TestReseedable, TestReseedableSubUnary)
{
    EXPECT_EQ(-5, (-x).module->GetValue(5, 43, 3));
    EXPECT_EQ(4, (-y).module->GetValue(5, -4, 34));
}
TEST_F(TestReseedable, TestReseedableMulReseedable)
{
    EXPECT_EQ(-1440, (x * y).module->GetValue(-16., 90., 0));
    EXPECT_EQ(1024., (x * x).module->GetValue(32., 0, 0));
    EXPECT_EQ(15., (y * x).module->GetValue(-5., -3., 0));
    EXPECT_EQ(1., (y * y).module->GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMulDouble)
{
    EXPECT_EQ(-80., (x * 5.).module->GetValue(-16., 0, 0));
    EXPECT_EQ(12., (y * (-4)).module->GetValue(-5., -3., 0));
}
TEST_F(TestReseedable, TestReseedableBlend)
{
    EXPECT_EQ(0.75, c05.blend(x, y).module->GetValue(0., 1., 5.));
    EXPECT_EQ(-5, (c05).blend(y, x).module->GetValue(-1, -17, 5.));
}
TEST_F(TestReseedable, TestReseedableSelect)
{
    EXPECT_EQ(-17, c05.select(x, y).module->GetValue(-1, -17, 5.));
    EXPECT_EQ(0., c05.select(y, x).module->GetValue(0., 1., 5.));

}
TEST_F(TestReseedable, TestReseedableDisplace)
{
    EXPECT_TRUE(false) << "Test not implemented";

}
TEST_F(TestReseedable, TestReseedableRotatePoint)
{
    EXPECT_EQ(20., x.rotatePoint(0,0,90).module->GetValue(2, 20, 200));
    EXPECT_EQ(-30, y.rotatePoint(0,0,180).module->GetValue(2, 30, 200));

}
TEST_F(TestReseedable, TestReseedableScalePoint)
{
    EXPECT_EQ(6., x.scalePoint(3, 30, 300).module->GetValue(2, 20, 200));
    EXPECT_EQ(200., y.scalePoint(-1, -10, -100).module->GetValue(2, -20, 200));

}
TEST_F(TestReseedable, TestReseedableTranslatePoint)
{
    EXPECT_EQ(3., x.translatePoint(1, 10, 100).module->GetValue(2, 20, 200));
    EXPECT_EQ(-10., y.translatePoint(1, 10, 100).module->GetValue(2, -20, 200));
}
TEST_F(TestReseedable, TestReseedableTurbulence)
{
    EXPECT_TRUE(false) << "Test not implemented";

}