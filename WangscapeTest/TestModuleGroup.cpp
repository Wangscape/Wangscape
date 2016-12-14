#include <gtest/gtest.h>

#include <ModuleFactories.h>

class TestModuleGroup : public ::testing::Test {
protected:
    Reseedable rs;
    TestModuleGroup() :
        rs(makePlaceholder())
    {

    };
    ~TestModuleGroup() {};
};

TEST_F(TestModuleGroup, TestGetValue)
{
    rs.first.get()->GetValue(0.,1.,2.);
}

TEST_F(TestModuleGroup, TestSetSeed)
{
    rs.second(293847928);
}