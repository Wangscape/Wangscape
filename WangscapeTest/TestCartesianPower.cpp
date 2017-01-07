#include <gtest/gtest.h>

#include <vector>

#include <tilegen/CartesianPower.h>

class TestCartesianPower : public ::testing::Test
{
protected:
    TestCartesianPower()
    {

    };
    ~TestCartesianPower() {};
};

TEST_F(TestCartesianPower, TestCartesianPowerValues)
{
    std::vector<int> base{4, 5, 6};
    const tilegen::CartesianPower<std::vector<int>::const_iterator> cp(base, 4);
    EXPECT_EQ(81, cp.size()) <<
        "CartesianProduct has incorrect size";
    auto cpit = cp.cbegin();
    for (size_t i = 0; i < 4; i++)
    {
        EXPECT_EQ(4, *cpit.get(i)) <<
            "CartesianProduct.cbegin() has incorrect value";
    }
    EXPECT_NE(cp.cbegin(), cp.cend());
    ++cpit;
    EXPECT_EQ(5, *cpit.get(0));
    EXPECT_EQ(4, *cpit.get(1));
    EXPECT_EQ(4, *cpit.get(2));
    EXPECT_EQ(4, *cpit.get(3));
    ++cpit; ++cpit;
    EXPECT_EQ(4, *cpit.get(0));
    EXPECT_EQ(5, *cpit.get(1));
    EXPECT_EQ(4, *cpit.get(2));
    EXPECT_EQ(4, *cpit.get(3));
    std::advance(cpit, 77);
    EXPECT_EQ(6, *cpit.get(0));
    EXPECT_EQ(6, *cpit.get(1));
    EXPECT_EQ(6, *cpit.get(2));
    EXPECT_EQ(6, *cpit.get(3));
    ++cpit;
    EXPECT_EQ(cpit, cp.cend());
    size_t count = 0;
    const auto& cpc(cp);
    std::as_const(cp);
    for (const auto& it : cp)
    {
        count++;
    }
    EXPECT_EQ(count, cp.size());
}