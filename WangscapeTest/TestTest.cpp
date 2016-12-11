#include <gtest/gtest.h>

class TestTest : public ::testing::Test {
protected:
    virtual void SetUp()
    {

    }
    virtual void TearDown()
    {
        
    }
};

TEST_F(TestTest, multiplyStuff)
{
        const int x = 4;
        const int y = 5;
        EXPECT_EQ(20, x*y);
        EXPECT_EQ(6, 2*3);
}
