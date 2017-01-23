#include <gtest/gtest.h>

#include <type_traits>

#include <utils.h>

template<typename I>
class TestPowIntSigned : public ::testing::Test
{
protected:
    const I min = std::numeric_limits<I>::min();
    const I minus_five = -5;
    const I minus_three = -3;
    const I minus_two = -2;
    const I minus_one = -1;
    const I zero = 0;
    const I one = 1;
    const I two = 2;
    const I three = 3;
    const I five = 5;
    const I digits = std::numeric_limits<I>::digits;
    const I max = std::numeric_limits<I>::max();
};

typedef ::testing::Types<
    char, short, int, long, long long>
    SignedIntTypes;
TYPED_TEST_CASE(TestPowIntSigned, SignedIntTypes);

TYPED_TEST(TestPowIntSigned, TestPowIntSignedX0)
{
    EXPECT_EQ(this->one, ipow(this->minus_one, this->zero));
    EXPECT_EQ(this->one, ipow(this->minus_two, this->zero));
    EXPECT_EQ(this->one, ipow(this->minus_three, this->zero));
    EXPECT_EQ(this->one, ipow(this->min, this->zero));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSigned0X)
{
    EXPECT_ANY_THROW(ipow(this->zero, this->minus_one));
    EXPECT_ANY_THROW(ipow(this->zero, this->minus_two));
    EXPECT_ANY_THROW(ipow(this->zero, this->minus_three));
    EXPECT_ANY_THROW(ipow(this->zero, this->min));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSignedX1)
{
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->one));
    EXPECT_EQ(this->minus_two, ipow(this->minus_two, this->one));
    EXPECT_EQ(this->minus_three, ipow(this->minus_three, this->one));
    EXPECT_EQ(this->min, ipow(this->min, this->one));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSigned1X)
{
    EXPECT_EQ(this->one, ipow(this->one, this->minus_one));
    EXPECT_EQ(this->one, ipow(this->one, this->minus_two));
    EXPECT_EQ(this->one, ipow(this->one, this->minus_three));
    EXPECT_EQ(this->one, ipow(this->one, this->min));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSignedMinus1X)
{
    EXPECT_EQ(this->one, ipow(this->minus_one, this->min));
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->minus_three));
    EXPECT_EQ(this->one, ipow(this->minus_one, this->minus_two));
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->minus_one));
    EXPECT_EQ(this->one, ipow(this->minus_one, this->zero));
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->one));
    EXPECT_EQ(this->one, ipow(this->minus_one, this->two));
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->three));
    EXPECT_EQ(this->minus_one, ipow(this->minus_one, this->max));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSignedExamples)
{
    EXPECT_EQ(4, ipow(this->minus_two, this->two));
    EXPECT_EQ(9, ipow(this->minus_three, this->two));
    EXPECT_EQ(25, ipow(this->minus_five, this->two));

    EXPECT_EQ(-8, ipow(this->minus_two, this->three));
    EXPECT_EQ(-27, ipow(this->minus_three, this->three));
    EXPECT_EQ(-125, ipow(this->minus_five, this->three));

    EXPECT_EQ(-32, ipow(this->minus_two, this->five));
}

TYPED_TEST(TestPowIntSigned, TestPowIntSignedMin)
{
    EXPECT_EQ(this->min, ipow(this->minus_two, this->digits));
}
