#include <gtest/gtest.h>

#include <vector>

#include <tilegen/CartesianPower.h>

class TestCartesianPower : public ::testing::Test
{
protected:
    typedef std::vector<int> Container;
    typedef std::vector<int>::const_iterator Iterator;

    Container base{4, 5, 6};
    const tilegen::CartesianPower<Iterator> cp{base, 4};
    TestCartesianPower()
    {

    };
    ~TestCartesianPower() {};
};

TEST_F(TestCartesianPower, TestCartesianPowerSize)
{
    EXPECT_EQ(81, cp.size()) <<
        "CartesianProduct has incorrect size";
}

TEST_F(TestCartesianPower, TestCartesianPowerCount)
{
    size_t count = 0;
    for (const auto& it : cp)
        count++;
    EXPECT_EQ(81, count);
}

TEST_F(TestCartesianPower, TestCartesianPowerComparisonBeginEnd)
{
    EXPECT_EQ(cp.cbegin(), cp.cbegin());
    EXPECT_NE(cp.cend(), cp.cbegin());
    EXPECT_NE(cp.cbegin(), cp.cend());
    EXPECT_EQ(cp.cend(), cp.cend());

    EXPECT_EQ(cp.cbegin(), cp.begin());
    EXPECT_EQ(cp.cend(), cp.end());
}

TEST_F(TestCartesianPower, TestCartesianPowerComparisonLast)
{
    auto it = cp.cbegin();
    for (size_t i = 0; i < cp.size(); i++)
    {
        ++it;
    }
    EXPECT_EQ(it, it);
    EXPECT_EQ(it, cp.cend());
    EXPECT_EQ(cp.cend(), it);
    EXPECT_NE(it, cp.cbegin());
    EXPECT_NE(cp.cbegin(), it);
}

TEST_F(TestCartesianPower, TestCartesianPowerComparisonOther)
{
    tilegen::CartesianPower<Iterator> cp1{base.cbegin() + 1, base.cend(), 4};
    tilegen::CartesianPower<Iterator> cp2{base.cbegin(), base.cend(), 3};
    EXPECT_NE(cp.begin(), cp1.begin());
    EXPECT_NE(cp.begin(), cp2.begin());
}

TEST_F(TestCartesianPower, TestCartesianPowerComparisonOtherMid)
{
    auto it = cp.cbegin();
    std::advance(it, 23);
    EXPECT_EQ(it, it);
    EXPECT_NE(it, cp.cbegin());
    EXPECT_NE(cp.cbegin(), it);
    EXPECT_NE(it, cp.cend());
    EXPECT_NE(cp.cend(), it);
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin)
{
    auto it = cp.cbegin();
    EXPECT_EQ(4, *it.get(0));
    EXPECT_EQ(4, *it.get(1));
    EXPECT_EQ(4, *it.get(2));
    EXPECT_EQ(4, *it.get(3));
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin1)
{
    auto it = cp.cbegin();
    ++it;
    EXPECT_EQ(5, *it.get(0));
    EXPECT_EQ(4, *it.get(1));
    EXPECT_EQ(4, *it.get(2));
    EXPECT_EQ(4, *it.get(3));
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin01)
{
    auto it = cp.cbegin();
    std::advance(it, 3);
    EXPECT_EQ(4, *it.get(0));
    EXPECT_EQ(5, *it.get(1));
    EXPECT_EQ(4, *it.get(2));
    EXPECT_EQ(4, *it.get(3));
}

TEST_F(TestCartesianPower, TestCartesianPowerValueLast)
{
    auto it = cp.cbegin();
    std::advance(it, 80);
    EXPECT_EQ(6, *it.get(0));
    EXPECT_EQ(6, *it.get(1));
    EXPECT_EQ(6, *it.get(2));
    EXPECT_EQ(6, *it.get(3));
}
