#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include <tilegen/CoordinatePacker.h>

class TestCoordinatePacker : public ::testing::Test
{
protected:
};

TEST_F(TestCoordinatePacker, TestCoordinatePackerDomain)
{
    for (auto i : {0, 1, 2, 10})
    {
        tilegen::CoordinatePacker<size_t> coord_packer(i);
        EXPECT_ANY_THROW(coord_packer.addCoordinate(-1));
        EXPECT_ANY_THROW(coord_packer.addCoordinate(i));
        EXPECT_ANY_THROW(coord_packer.addCoordinate(i + 1));
    }
}
TEST_F(TestCoordinatePacker, TestCoordinatePackerSize)
{
    tilegen::CoordinatePacker<size_t> coord_packer0(0);
    EXPECT_EQ(0, coord_packer0.size());
    tilegen::CoordinatePacker<size_t> coord_packer1(1);
    EXPECT_EQ(1, coord_packer1.size());
    tilegen::CoordinatePacker<size_t> coord_packer2(2);
    EXPECT_EQ(2, coord_packer2.size());
    tilegen::CoordinatePacker<size_t> coord_packer10(10);
    EXPECT_EQ(10, coord_packer10.size());
}

TEST_F(TestCoordinatePacker, TestCoordinatePacker1)
{
    tilegen::CoordinatePacker<size_t> coord_packer(1);
    EXPECT_EQ(0, coord_packer.packed());
    coord_packer.addCoordinate(0);
    EXPECT_EQ(0, coord_packer.packed());
}


TEST_F(TestCoordinatePacker, TestCoordinatePacker2)
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

TEST_F(TestCoordinatePacker, TestCoordinatePacker10)
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
    coord_packer.addCoordinate(0);
    EXPECT_EQ(12350, coord_packer.packed());
}
