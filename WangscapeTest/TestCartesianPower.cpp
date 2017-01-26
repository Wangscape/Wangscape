#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include <tilegen/CartesianPower.h>

class TestCartesianPower : public ::testing::Test
{
protected:
    typedef std::vector<int> Container;
    typedef std::vector<int>::const_iterator Iterator;

    Container base{4, 5, 6};
    const tilegen::CartesianPower<Iterator> cp{base, 4};
};

TEST_F(TestCartesianPower, TestCartesianPowerSize)
{
    EXPECT_EQ(81, cp.size()) <<
        "CartesianProduct has incorrect size";
}

TEST_F(TestCartesianPower, TestCartesianPowerCount)
{
    ptrdiff_t count = std::distance(cp.cbegin(), cp.cend());
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
    std::advance(it, cp.size());
    EXPECT_EQ(it, it);
    EXPECT_EQ(it, cp.cend());
    EXPECT_EQ(cp.cend(), it);
    EXPECT_NE(it, cp.cbegin());
    EXPECT_NE(cp.cbegin(), it);
}

TEST_F(TestCartesianPower, TestCartesianPowerComparisonOther)
{
    tilegen::CartesianPower<Iterator> cp1{base.cbegin() + 1, 2, 4};
    tilegen::CartesianPower<Iterator> cp2{base.cbegin(), base.size(), 3};
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

TEST_F(TestCartesianPower, TestCartesianPowerIteratorPostIncrement)
{
    auto it = cp.cbegin();
    Container v1{4, 4, 4, 4};
    Container v2{5, 4, 4, 4};
    EXPECT_EQ(v1, *it);
    auto x = *(it++);
    EXPECT_EQ(v1, x);
    EXPECT_EQ(v2, *it);
}

TEST_F(TestCartesianPower, TestCartesianPowerRange)
{
    auto first = base.cbegin();
    auto size = base.size();
    EXPECT_EQ(first, cp.first);
    EXPECT_EQ(size, cp.baseSize);
    EXPECT_EQ(first, cp.cbegin().getFirst());
    EXPECT_EQ(size, cp.cbegin().getBaseSize());
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin)
{
    auto it = cp.cbegin();
    EXPECT_EQ(4, it.getValues()[0]);
    EXPECT_EQ(4, it.getValues()[1]);
    EXPECT_EQ(4, it.getValues()[2]);
    EXPECT_EQ(4, it.getValues()[3]);
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin1)
{
    auto it = cp.cbegin();
    ++it;
    EXPECT_EQ(5, it.getValues()[0]);
    EXPECT_EQ(4, it.getValues()[1]);
    EXPECT_EQ(4, it.getValues()[2]);
    EXPECT_EQ(4, it.getValues()[3]);
}

TEST_F(TestCartesianPower, TestCartesianPowerValueBegin01)
{
    auto it = cp.cbegin();
    std::advance(it, 3);
    EXPECT_EQ(4, it.getValues()[0]);
    EXPECT_EQ(5, it.getValues()[1]);
    EXPECT_EQ(4, it.getValues()[2]);
    EXPECT_EQ(4, it.getValues()[3]);
}

TEST_F(TestCartesianPower, TestCartesianPowerValueLast)
{
    auto it = cp.cbegin();
    std::advance(it, 80);
    EXPECT_EQ(6, it.getValues()[0]);
    EXPECT_EQ(6, it.getValues()[1]);
    EXPECT_EQ(6, it.getValues()[2]);
    EXPECT_EQ(6, it.getValues()[3]);
    ++it;
    EXPECT_EQ(it, cp.cend());
}

TEST_F(TestCartesianPower, TestCartesianPowerCoordinates)
{
    auto it = cp.cbegin();
    std::advance(it, 15);

    EXPECT_EQ(0, it.getCoordinates()[0]);
    EXPECT_EQ(2, it.getCoordinates()[1]);
    EXPECT_EQ(1, it.getCoordinates()[2]);
    EXPECT_EQ(0, it.getCoordinates()[3]);
}

TEST_F(TestCartesianPower, TestCartesianPowerArrow)
{
    auto it = cp.cbegin();
    EXPECT_EQ(cp.power, it->size());
}

TEST_F(TestCartesianPower, TestCartesianPowerValues)
{
    auto it = cp.cbegin();
    std::advance(it, 15);
    const std::vector<int>& values = *it;

    EXPECT_EQ(4, values[0]);
    EXPECT_EQ(6, values[1]);
    EXPECT_EQ(5, values[2]);
    EXPECT_EQ(4, values[3]);

    EXPECT_EQ(values, it.getValues());
}
TEST_F(TestCartesianPower, TestCartesianPowerSize2D)
{
    std::pair<size_t, size_t> size{45, 45};
    EXPECT_EQ(size, cp.size2D(5));
    size = {45, 15};
    EXPECT_EQ(size, tilegen::CartesianPower<Iterator>(base, 3).size2D(5));
}

TEST_F(TestCartesianPower, TestCartesianPowerCoordinates2D)
{
    std::set<std::pair<size_t, size_t>> coordinates_used;
    for (auto it = cp.cbegin(); it != cp.cend(); ++it)
    {
        std::pair<size_t, size_t> coords = it.coordinates2D();
        EXPECT_LE((size_t)0, coords.first);
        EXPECT_GT((size_t)9, coords.first);
        EXPECT_LE((size_t)0, coords.second);
        EXPECT_GT((size_t)9, coords.second);
        EXPECT_TRUE(coordinates_used.insert(coords).second);
    }
}
