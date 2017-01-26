#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include <tilegen/CoordinatePacker.h>

class TestCoordinatePacker : public ::testing::Test
{
public:
    std::vector<size_t> base_values{0, 1, 2, 10};
};

TEST_F(TestCoordinatePacker, TestCoordinatePackerDomain)
{
    for (auto i : base_values)
    {
        tilegen::CoordinatePacker<size_t> coord_packer(i);
        if (i > 0)
        {
            EXPECT_NO_THROW(coord_packer.addCoordinate(0));
            EXPECT_NO_THROW(coord_packer.addCoordinate(i - 1));
        }
        if (i > 1)
        {
            EXPECT_NO_THROW(coord_packer.addCoordinate(1));
        }
        if (i > 2)
        {
            EXPECT_NO_THROW(coord_packer.addCoordinate(2));
        }
        EXPECT_ANY_THROW(coord_packer.addCoordinate(-1));
        EXPECT_ANY_THROW(coord_packer.addCoordinate(i));
        EXPECT_ANY_THROW(coord_packer.addCoordinate(i + 1));
    }
}
TEST_F(TestCoordinatePacker, TestCoordinatePackerSize)
{
    for (auto i : base_values)
    {
        tilegen::CoordinatePacker<size_t> coord_packer(i);
        EXPECT_EQ(i, coord_packer.size());
    }
}

TEST_F(TestCoordinatePacker, TestCoordinatePackerValuesBase1)
{
    tilegen::CoordinatePacker<size_t> coord_packer(1);
    EXPECT_EQ(0, coord_packer.packed());
    coord_packer.addCoordinate(0);
    EXPECT_EQ(0, coord_packer.packed());
}


TEST_F(TestCoordinatePacker, TestCoordinatePackerValuesBase2)
{
    tilegen::CoordinatePacker<size_t> coord_packer(2);
    EXPECT_EQ(0, coord_packer.packed());
    coord_packer.addCoordinate(1);
    EXPECT_EQ(1, coord_packer.packed());
    coord_packer.addCoordinate(0);
    EXPECT_EQ(2, coord_packer.packed());
    coord_packer.addCoordinate(1);
    EXPECT_EQ(5, coord_packer.packed());
    coord_packer.addCoordinate(0);
    EXPECT_EQ(10, coord_packer.packed());
    coord_packer.addCoordinate(1);
    EXPECT_EQ(21, coord_packer.packed());
}

TEST_F(TestCoordinatePacker, TestCoordinatePackerValuesBase10)
{
    tilegen::CoordinatePacker<size_t> coord_packer(10);
    EXPECT_EQ(0, coord_packer.packed());
    coord_packer.addCoordinate(1);
    EXPECT_EQ(1, coord_packer.packed());
    coord_packer.addCoordinate(2);
    EXPECT_EQ(12, coord_packer.packed());
    coord_packer.addCoordinate(3);
    EXPECT_EQ(123, coord_packer.packed());
    coord_packer.addCoordinate(5);
    EXPECT_EQ(1235, coord_packer.packed());
    coord_packer.addCoordinate(9);
    EXPECT_EQ(12359, coord_packer.packed());
    coord_packer.addCoordinate(0);
    EXPECT_EQ(123590, coord_packer.packed());
}
