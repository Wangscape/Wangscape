#include <gtest/gtest.h>

#include <noise/module/ReseedableOps.h>

class TestReseedable : public ::testing::Test {
protected:
    noise::module::ReseedablePtr x;
    noise::module::ReseedablePtr y;
    noise::module::ReseedablePtr c05;
    TestReseedable() :
        x(noise::module::makeX()),
        y(noise::module::makeY()),
        c05(noise::module::makeConst(0.5))
    {
    };
    ~TestReseedable() {};
};

TEST_F(TestReseedable, TestReseedableGetValue)
{
    EXPECT_EQ(2508., x->getModule().GetValue(2508., -518., 2805.)) <<
        "Incorrect value";
    EXPECT_EQ(1., y->getModule().GetValue(320., 1., -39.)) <<
        "Incorrect value";
}

TEST_F(TestReseedable, TestReseedableSetSeed)
{
    EXPECT_NO_THROW({ x->setSeed(35089); });
    EXPECT_NO_THROW({ y->setSeed(293847928); });
}


TEST_F(TestReseedable, TestReseedableAbs)
{
    EXPECT_EQ(5., abs(x)->getModule().GetValue(-5., 0, 0));
    EXPECT_EQ(4., abs(x)->getModule().GetValue(4., 0, 0));
    EXPECT_EQ(3., abs(y)->getModule().GetValue(-5., 3., 0));
    EXPECT_EQ(2., abs(y)->getModule().GetValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedableClamp)
{
    EXPECT_EQ(-1., clamp(x, -1., 1.)->getModule().GetValue(-5., 0, 0));
    EXPECT_EQ(1., clamp(y, -1., 1.)->getModule().GetValue(-1., 3., 0));
    EXPECT_EQ(0., clamp(x, -5., 5.)->getModule().GetValue(0., 3., 0));
    EXPECT_EQ(-10., clamp(y, -10, -10)->getModule().GetValue(4., -2., 0));
}

TEST_F(TestReseedable, TestReseedablePowDouble)
{
    EXPECT_NEAR(-8., pow(x, 3)->getModule().GetValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(0.04, pow(x, -2)->getModule().GetValue(5., 0, 0));
    EXPECT_NEAR(3., pow(y, 0.5)->getModule().GetValue(-5., 9., 0), 0.0001);
    EXPECT_EQ(1., pow(y, 0)->getModule().GetValue(4., -2., 5.));
}

TEST_F(TestReseedable, TestReseedablePowReseedable)
{
    EXPECT_EQ(4., pow(x, x)->getModule().GetValue(2., 0, 0));
    EXPECT_EQ(-32., pow(x, y)->getModule().GetValue(-2., 5, 0));
    EXPECT_NEAR(-1953125., pow(y, x)->getModule().GetValue(9., -5., 0), 0.01);
    EXPECT_EQ(1. / 256., pow(y, y)->getModule().GetValue(4., -4., 5.));
}

TEST_F(TestReseedable, TestReseedableExpDouble)
{
    EXPECT_NEAR(1./9., pow(3., x)->getModule().GetValue(-2., 0, 0), 0.0001);
    EXPECT_EQ(-32., pow(-2., x)->getModule().GetValue(5., 0, 0));
    EXPECT_NEAR(0.25, pow(0.5, y)->getModule().GetValue(-5., 2., 0), 0.0001);
    EXPECT_EQ(0., pow(0., y)->getModule().GetValue(4., 2., 5.));
}

TEST_F(TestReseedable, TestReseedableInv)
{
    EXPECT_EQ(16., invert(x)->getModule().GetValue(-16., 0, 0));
    EXPECT_EQ(-32., invert(x)->getModule().GetValue(32., 0, 0));
    EXPECT_EQ(3., invert(y)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(-1., invert(y)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableScaleBias)
{
    EXPECT_EQ(-155, scaleBias(x, 10, 5)->getModule().GetValue(-16., 0, 0));
    EXPECT_EQ(-158, scaleBias(x, -5, 2)->getModule().GetValue(32., 0, 0));
    EXPECT_EQ(1.5, scaleBias(y, 0.5, 3)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1.5, scaleBias(y, 1, 0.5)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddReseedable)
{
    EXPECT_EQ(74., (x + y)->getModule().GetValue(-16., 90., 0));
    EXPECT_EQ(64., (x + x)->getModule().GetValue(32., 0, 0));
    EXPECT_EQ(-8., (y + x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(2., (y + y)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableAddDouble)
{
    EXPECT_EQ(-11., (x + 5.)->getModule().GetValue(-16., 0, 0));
    EXPECT_EQ(-6., (y + (-3))->getModule().GetValue(-5., -3., 0));
}

TEST_F(TestReseedable, TestReseedableAddAssign)
{
    noise::module::ReseedablePtr r1 = x;
    r1 += y;
    noise::module::ReseedablePtr r2 = y;
    r2 += x;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(74., r1->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(-3., y->getModule().GetValue(-5., -3, 999.));
    EXPECT_EQ(-8., r2->getModule().GetValue(-5., -3., 999.));
}

TEST_F(TestReseedable, TestReseedableAddAssignDouble)
{
    noise::module::ReseedablePtr r = x;
    r += 24;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 345., 876.));
    EXPECT_EQ(19., r->getModule().GetValue(-5., -365., 195.));
}

TEST_F(TestReseedable, TestReseedableMaxReseedable)
{
    EXPECT_EQ(-3., max(x, y)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(4., max(y, x)->getModule().GetValue(4., 1., 5.));
    EXPECT_EQ(-3., max(y, x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(4., max(x, y)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMaxDouble)
{
    EXPECT_EQ(4., max(x, 4.)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1., max(0., y)->getModule().GetValue(4., 1., 5.));
    EXPECT_EQ(4., max(4., x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1., max(y, 0.)->getModule().GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMinReseedable)
{
    EXPECT_EQ(-5., min(x, y)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1., min(y, x)->getModule().GetValue(4., 1., 5.));
    EXPECT_EQ(-5., min(y, x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1., min(x, y)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableMinDouble)
{
    EXPECT_EQ(-5., min(x, 4)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(0., min(0, y)->getModule().GetValue(4., 1., 5.));
    EXPECT_EQ(-5., min(4, x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(0., min(y, 0)->getModule().GetValue(4., 1., 5.));
}

TEST_F(TestReseedable, TestReseedableSubReseedable)
{
    EXPECT_EQ(-106., (x - y)->getModule().GetValue(-16., 90., 0));
    EXPECT_EQ(0., (x - x)->getModule().GetValue(32., 0, 0));
    EXPECT_EQ(2., (y - x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(0., (y - y)->getModule().GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableSubDouble)
{
    EXPECT_EQ(-21., (x - 5.)->getModule().GetValue(-16., 0, 0));
    EXPECT_EQ(1., (y - (-4))->getModule().GetValue(-5., -3., 0));
}
TEST_F(TestReseedable, TestReseedableSubUnary)
{
    EXPECT_EQ(-5, (-x)->getModule().GetValue(5, 43, 3));
    EXPECT_EQ(4, (-y)->getModule().GetValue(5, -4, 34));
}

TEST_F(TestReseedable, TestReseedableSubAssign)
{
    noise::module::ReseedablePtr r1 = x;
    r1 -= y;
    noise::module::ReseedablePtr r2 = y;
    r2 -= x;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(-106., r1->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(-3., y->getModule().GetValue(-5., -3, 999.));
    EXPECT_EQ(2., r2->getModule().GetValue(-5., -3., 999.));
}

TEST_F(TestReseedable, TestReseedableSubAssignDouble)
{
    noise::module::ReseedablePtr r = x;
    r -= 24.;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 345., 876.));
    EXPECT_EQ(-40., r->getModule().GetValue(-16., -365., 195.));
}

TEST_F(TestReseedable, TestReseedableMulReseedable)
{
    EXPECT_EQ(-1440, (x * y)->getModule().GetValue(-16., 90., 0));
    EXPECT_EQ(1024., (x * x)->getModule().GetValue(32., 0, 0));
    EXPECT_EQ(15., (y * x)->getModule().GetValue(-5., -3., 0));
    EXPECT_EQ(1., (y * y)->getModule().GetValue(4., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableMulDouble)
{
    EXPECT_EQ(-80., (x * 5.)->getModule().GetValue(-16., 0, 0));
    EXPECT_EQ(12., (y * (-4))->getModule().GetValue(-5., -3., 0));
}

TEST_F(TestReseedable, TestReseedableMulAssign)
{
    noise::module::ReseedablePtr r1 = x;
    r1 *= y;
    noise::module::ReseedablePtr r2 = y;
    r2 *= x;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(-1440., r1->getModule().GetValue(-16., 90., 999.));
    EXPECT_EQ(-3., y->getModule().GetValue(-5., -3, 999.));
    EXPECT_EQ(15., r2->getModule().GetValue(-5., -3., 999.));
}

TEST_F(TestReseedable, TestReseedableMulAssignDouble)
{
    noise::module::ReseedablePtr r = x;
    r *= 2.5;
    EXPECT_EQ(-16., x->getModule().GetValue(-16., 345., 876.));
    EXPECT_EQ(-40., r->getModule().GetValue(-16., -365., 195.));
}

TEST_F(TestReseedable, TestReseedableBlend)
{
    EXPECT_EQ(0.75, blend(c05, x, y)->getModule().GetValue(0., 1., 5.));
    EXPECT_EQ(-5, blend(c05, y, x)->getModule().GetValue(-1, -17, 5.));
}
TEST_F(TestReseedable, TestReseedableSelect)
{
    EXPECT_EQ(-17, select(c05, x, y)->getModule().GetValue(-1, -17, 5.));
    EXPECT_EQ(0., select(c05, y, x)->getModule().GetValue(0., 1., 5.));
}
TEST_F(TestReseedable, TestReseedableDisplace)
{
    auto displace = translate((x - (y * 2)), x, y, c05);
    EXPECT_EQ(0., displace->getModule().GetValue(0, 0, 304958.));
    EXPECT_EQ(0., displace->getModule().GetValue(2, 1, 30458.));
    EXPECT_EQ(-16., displace->getModule().GetValue(-2, 3, 30458.));
}
TEST_F(TestReseedable, TestReseedableRotatePoint)
{
    EXPECT_EQ(20., rotatePoint(x, 0,0,90)->getModule().GetValue(2, 20, 200));
    EXPECT_EQ(-30, rotatePoint(y, 0,0,180)->getModule().GetValue(2, 30, 200));

}
TEST_F(TestReseedable, TestReseedableScalePoint)
{
    EXPECT_EQ(6., scalePoint(x, 3, 30, 300)->getModule().GetValue(2, 20, 200));
    EXPECT_EQ(200., scalePoint(y, -1, -10, -100)->getModule().GetValue(2, -20, 200));

}
TEST_F(TestReseedable, TestReseedableTranslatePoint)
{
    EXPECT_EQ(3., translate(x, 1, 10, 100)->getModule().GetValue(2, 20, 200));
    EXPECT_EQ(-10., translate(y, 1, 10, 100)->getModule().GetValue(2, -20, 200));
}
TEST_F(TestReseedable, TestReseedableTurbulence)
{
    auto turb = turbulence(c05, 2., 2., 3, 0);
    EXPECT_EQ(0.5, turb->getModule().GetValue(346980., 0.63, 696.346));
}

TEST_F(TestReseedable, TestReseedableConst)
{
    EXPECT_EQ(3.6345, noise::module::makeConst(3.6345)->getModule().GetValue(52935874, 57432895, 2549));
    EXPECT_EQ(-3045.25, noise::module::makeConst(-3045.25)->getModule().GetValue(259, 594, 239587));
}

TEST_F(TestReseedable, TestReseedableTerraceManual)
{
    std::vector<double> control_points{0., 0.5, 1.};
    noise::module::ReseedablePtr terr = terrace(x, control_points.cbegin(), control_points.cend());

    EXPECT_NEAR(0., terr->getModule().GetValue(0., 239478, -23984), 0.00001);
    EXPECT_NEAR(0.5, terr->getModule().GetValue(0.5, -239478, -23984), 0.00001);
    EXPECT_NEAR(1., terr->getModule().GetValue(1., -239478, 23984), 0.00001);

    EXPECT_GT(0.25, terr->getModule().GetValue(0.25, 3957, -9723));
    EXPECT_GT(0.75, terr->getModule().GetValue(0.75, -3957, 9723));
}

TEST_F(TestReseedable, TestReseedableTerraceAuto)
{
    noise::module::ReseedablePtr terr = terrace(y, 4, true);

    EXPECT_NEAR(-1., terr->getModule().GetValue(239478, -1, -23984), 0.00001);
    EXPECT_NEAR(-1. / 3., terr->getModule().GetValue(-239478, -1. / 3., -23984), 0.00001);
    EXPECT_NEAR(1. / 3., terr->getModule().GetValue(-239478, 1. / 3., 23984), 0.00001);
    EXPECT_NEAR(1., terr->getModule().GetValue(239478, 1., 23984), 0.00001);

    EXPECT_LT(-2. / 3., terr->getModule().GetValue(3957, -2. / 3., -9723));
    EXPECT_LT(0., terr->getModule().GetValue(-3957, 0., -9723));
    EXPECT_LT(2. / 3., terr->getModule().GetValue(-3957, 2. / 3., 9723));
}


TEST_F(TestReseedable, TestReseedableCurve)
{
    std::vector<std::pair<double, double>> control_points{{-1, 1}, {0, -1}, {1, 1}};
    noise::module::ReseedablePtr crv = curve(x, control_points.cbegin(), control_points.cend());

    EXPECT_NEAR(1., crv->getModule().GetValue(-1., 239478, -23984), 0.00001);
    EXPECT_NEAR(-1, crv->getModule().GetValue(0., -239478, -23984), 0.00001);
    EXPECT_NEAR(1., crv->getModule().GetValue(1., -239478, 23984), 0.00001);

    EXPECT_GT(0.9, crv->getModule().GetValue(-0.5, 3957, -9723));
    EXPECT_LT(-0.9, crv->getModule().GetValue(-0.5, -3957, -9723));
    EXPECT_GT(0.9, crv->getModule().GetValue(0.5, -3957, 9723));
    EXPECT_LT(-0.9, crv->getModule().GetValue(0.5, -3957, 9723));
}
