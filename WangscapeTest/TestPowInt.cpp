#include <gtest/gtest.h>

#include <type_traits>

#include <utils.h>

template<typename I>
class TestPowInt : public ::testing::Test
{
protected:
    const I zero;
    const I one;
    const I two;
    const I three;
    const I five;
    const I max;
    const I digits;
    TestPowInt()
    {
        zero = 0;
        one = 1;
        two = 2;
        three = 3;
        five = 5;
        max = std::numeric_limits<I>::max();
        digits = static_cast<I>(std::numeric_limits<I>::digits);

    };
};

typedef ::testing::Types<
    char, short, int, long, long long,
    unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>
    IntTypes;
TYPED_TEST_CASE(TestPowInt, IntTypes);

TYPED_TEST(TestPowInt, TestPowInt00)
{
    EXPECT_EQ(this->one, ipow(this->zero, this->zero));
}

TYPED_TEST(TestPowInt, TestPowIntX0)
{
    EXPECT_EQ(this->one, ipow(this->one, this->zero));
    EXPECT_EQ(this->one, ipow(this->two, this->zero));
    EXPECT_EQ(this->one, ipow(this->three, this->zero));
    EXPECT_EQ(this->one, ipow(this->five, this->zero));
    EXPECT_EQ(this->one, ipow(this->digits, this->zero));
    EXPECT_EQ(this->one, ipow(this->max, this->zero));
}

TYPED_TEST(TestPowInt, TestPowInt0X)
{
    EXPECT_EQ(this->zero, ipow(this->zero, this->one));
    EXPECT_EQ(this->zero, ipow(this->zero, this->two));
    EXPECT_EQ(this->zero, ipow(this->zero, this->three));
    EXPECT_EQ(this->zero, ipow(this->zero, this->five));
    EXPECT_EQ(this->zero, ipow(this->zero, this->digits));
    EXPECT_EQ(this->zero, ipow(this->zero, this->max));
}

TYPED_TEST(TestPowInt, TestPowIntX1)
{
    EXPECT_EQ(this->one, ipow(this->one, this->one));
    EXPECT_EQ(this->two, ipow(this->two, this->one));
    EXPECT_EQ(this->three, ipow(this->three, this->one));
    EXPECT_EQ(this->max, ipow(max, this->one));
}

TYPED_TEST(TestPowInt, TestPowInt1X)
{
    EXPECT_EQ(this->one, ipow(this->one, this->one));
    EXPECT_EQ(this->one, ipow(this->one, this->two));
    EXPECT_EQ(this->one, ipow(this->one, this->digits));
    EXPECT_EQ(this->one, ipow(this->one, this->max));
}

TYPED_TEST(TestPowInt, TestPowIntExamples)
{
    EXPECT_EQ(4, ipow(this->two, this->two));
    EXPECT_EQ(9, ipow(this->three, this->two));
    EXPECT_EQ(25, ipow(this->five, this->two));
    EXPECT_EQ(this->one << (this->digits - 1),
              ipow(this->two,
                   TypeParam(this->digits - 1)));

    EXPECT_EQ(8, ipow(this->two, this->three));
    EXPECT_EQ(27, ipow(this->three, this->three));
    EXPECT_EQ(125, ipow(this->five, this->three));

    EXPECT_EQ(32, ipow(this->two, this->five));
}

TYPED_TEST(TestPowInt, TestPowIntTooLarge)
{
    EXPECT_ANY_THROW(ipow(this->two, this->digits));
    EXPECT_ANY_THROW(ipow(this->two, this->max));
    EXPECT_ANY_THROW(ipow(this->three, this->digits));
    EXPECT_ANY_THROW(ipow(this->three, this->max));
    EXPECT_ANY_THROW(ipow(this->max, this->digits));
    EXPECT_ANY_THROW(ipow(this->max, this->max));
}
