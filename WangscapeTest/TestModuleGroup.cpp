#include <gtest/gtest.h>

#include <noise/module/ModuleFactories.h>

class TestModuleGroup : public ::testing::Test
{
protected:
    noise::Reseedable rs;
    TestModuleGroup() :
        rs(noise::module::makePlaceholder())
    {
        // The current placeholder is a Reseedable,
        // but it's not a ModuleGroup.
        // Maybe these tests should be moved.
    };
    ~TestModuleGroup() {};
};

TEST_F(TestModuleGroup, TestGetValue)
{
    rs.getValue(0.,1.,2.);
}

TEST_F(TestModuleGroup, TestSetSeed)
{
    rs.setSeed(35089);
    double v = rs.getValue(2, 1, 0);
    rs.setSeed(293847928);
    ASSERT_NE(v, rs.getValue(2, 1, 0)) <<
        "Same value after reseed";
}