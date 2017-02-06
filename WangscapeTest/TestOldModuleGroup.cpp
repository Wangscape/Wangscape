#include <gtest/gtest.h>

#include <noise/module/ReseedableOps.h>

class TestOldModuleGroup : public ::testing::Test
{
protected:
    noise::module::ReseedablePtr rs;
    TestOldModuleGroup() :
        rs(noise::module::makePlaceholder())
    {
        // The current placeholder is a Reseedable,
        // but it's not a OldModuleGroup.
        // Maybe these tests should be moved.
    };
    ~TestOldModuleGroup() {};
};

TEST_F(TestOldModuleGroup, TestGetValue)
{
    rs->getValue(0.,1.,2.);
}

TEST_F(TestOldModuleGroup, TestSetSeed)
{
    rs->setSeed(35089);
    double v = rs->getValue(2, 1, 0);
    rs->setSeed(293847928);
    ASSERT_NE(v, rs->getValue(2, 1, 0)) <<
        "Same value after reseed";
}