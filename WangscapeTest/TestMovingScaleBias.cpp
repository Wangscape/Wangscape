#include <gtest/gtest.h>

#include <ModuleFactories.h>

class TestMovingScaleBias : public ::testing::Test {
protected:
    Reseedable x;
    Reseedable y;
    Reseedable msb;

    TestMovingScaleBias() :
        x(makeX()),
        y(makeY()),
        msb(makeMovingScaleBias(x,(y*2)+1,(y*3)+2))
    {

    };
    ~TestMovingScaleBias() {};
};

TEST_F(TestMovingScaleBias, TestMovingScaleBias)
{
    EXPECT_NEAR(1.5, msb.module->GetValue(0., 0., 3453.), 0.0001);
    EXPECT_NEAR(3., msb.module->GetValue(-1., 1., 3453.), 0.0001);
    EXPECT_NEAR(-1., msb.module->GetValue(345304895., -1., 3453.), 0.0001);
    EXPECT_NEAR(8., msb.module->GetValue(1., 2., 3453.), 0.0001);
}