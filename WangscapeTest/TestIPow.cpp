#include <gtest/gtest.h>

#include <type_traits>
#include <algorithm>
#include <tuple>

#include <ipow.h>

template<typename T>
class TestIPow : public ::testing::Test
{
public:
    typedef typename std::tuple_element<0, T>::type IBase;
    typedef typename std::tuple_element<1, T>::type IExp;
    const static bool UseBitshift = std::tuple_element<2, T>::type::value;

    std::vector<IBase> basesPositive;
    std::vector<IBase> basesNegative;
    std::vector<IExp> expsPositive;
    std::vector<IExp> expsNegative;
    std::vector<std::tuple<IBase, IExp, IBase>> examplesPositive;
    std::vector<std::tuple<IBase, IExp, IBase>> examplesNegative;
    const IBase baseZero = 0;
    const IBase baseOne = 1;
    const IBase baseTwo = 2;
    const IBase baseThree = 3;
    const IBase baseMax = std::numeric_limits<IBase>::max();
    const IBase baseMin = std::numeric_limits<IBase>::min();
    const IExp expZero = 0;
    const IExp expOne = 1;
    const IExp expDigits = static_cast<IExp>(std::numeric_limits<IBase>::digits);
    const IExp expDigitsMinusOne = expDigits - 1;
    IBase ipowWrapper(IBase base, IExp exp)
    {
        return ipow<IBase, IExp, UseBitshift>(base, exp);
    }
    TestIPow()
    {
        basesPositive = {1, 2, 3, baseMax};
        cpp::static_if<std::is_signed<IBase>::value>(
            [&](auto) {
            basesNegative = {IBase(-1), IBase(-2), IBase(-3), baseMin};
        });

        expsPositive = {1, 2, 3, expDigits};
        cpp::static_if<std::is_signed<IExp>::value>(
        [&](auto) {
            expsNegative = {-1, -2, -3, -expDigits};
        });

        examplesPositive = {
            {2, 2, 4},
            {2, 3, 8},
            {3, 2, 9},
            {3, 3, 27}
        };
        cpp::static_if<std::is_signed<IBase>::value>(
        [&](auto) {
            examplesNegative = {
                {-2, 2, 4},
                {-2, 3, -8},
                {-3, 2, 9},
                {-3, 3, -27}
        };
        });
    }
};

typedef ::testing::Types<
    std::tuple<unsigned char, unsigned char, std::false_type>,
    std::tuple<short, unsigned char, std::true_type>,
    std::tuple<unsigned int, int, std::true_type>,
    std::tuple<long long, long long, std::false_type>
>
    IPowArgs;
TYPED_TEST_CASE(TestIPow, IPowArgs);

TYPED_TEST(TestIPow, TestIPow00)
{
    EXPECT_EQ(this->baseOne, this->ipowWrapper(this->baseZero, this->expZero));
}

TYPED_TEST(TestIPow, TestIPowX0)
{
    for (auto base : this->basesPositive)
    {
        EXPECT_EQ(this->baseOne, this->ipowWrapper(base, this->expZero));
    }

    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
    ([&](auto) {
        for (auto base : this->basesNegative)
        {
            EXPECT_EQ(this->baseOne, this->ipowWrapper(base, this->expZero));
        }
    });
}

TYPED_TEST(TestIPow, TestIPow0X)
{
    for (auto exp : this->expsPositive)
    {
        EXPECT_EQ(this->baseZero, this->ipowWrapper(this->baseZero, exp));
    }

    cpp::static_if<std::is_signed<typename TestFixture::IExp>::value>
    ([&](auto) {
        for (auto exp : this->expsNegative)
        {
            EXPECT_ANY_THROW(this->ipowWrapper(this->baseZero, exp));
        }
    });
}

TYPED_TEST(TestIPow, TestIPowX1)
{
    for (auto base : this->basesPositive)
    {
        EXPECT_EQ(base, this->ipowWrapper(base, this->expOne));
    }

    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
    ([&](auto) {
        for (auto base : this->basesNegative)
        {
            EXPECT_EQ(base, this->ipowWrapper(base, this->expOne));
        }
    });
}

TYPED_TEST(TestIPow, TestIPow1X)
{
    for (auto exp : this->expsPositive)
    {
        EXPECT_EQ(this->baseOne, this->ipowWrapper(this->baseOne, exp));
    }

    cpp::static_if<std::is_signed<typename TestFixture::IExp>::value>
    ([&](auto) {
        for (auto exp : this->expsNegative)
        {
            EXPECT_EQ(this->baseOne, this->ipowWrapper(this->baseOne, exp));
        }
    });
}

TYPED_TEST(TestIPow, TestIPowMinus1X)
{

    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
    ([&](auto) {
        for (auto exp : this->expsPositive)
        {
            if (exp % 2)
                EXPECT_EQ(-this->baseOne, this->ipowWrapper(-this->baseOne, exp));
            else
                EXPECT_EQ(this->baseOne, this->ipowWrapper(-this->baseOne, exp));
        }
        cpp::static_if<std::is_signed<typename TestFixture::IExp>::value>
        ([&](auto) {
            for (auto exp : this->expsNegative)
            {
                if (exp % 2)
                    EXPECT_EQ(-this->baseOne, this->ipowWrapper(-this->baseOne, exp));
                else
                    EXPECT_EQ(this->baseOne, this->ipowWrapper(-this->baseOne, exp));
            }
        });
    });
}

TYPED_TEST(TestIPow, TestIPowExamples)
{
    for (auto example : this->examplesPositive)
    {
        EXPECT_EQ(std::get<2>(example), this->ipowWrapper(std::get<0>(example), std::get<1>(example)));
    }
    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
    ([&](auto) {
        for (auto example : this->examplesNegative)
        {
            EXPECT_EQ(std::get<2>(example), this->ipowWrapper(std::get<0>(example), std::get<1>(example)));
        }
    });
}

TYPED_TEST(TestIPow, TestIPowLargestResults)
{
    typename TestFixture::IBase highest = this->baseOne << this->expDigitsMinusOne;
    EXPECT_LT(this->baseTwo, highest);
    EXPECT_EQ(highest, this->ipowWrapper(this->baseTwo, this->expDigitsMinusOne));

    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value &&
                   std::numeric_limits<typename TestFixture::IBase>::digits % 2>
    ([&](auto) {
        if (std::is_signed<typename TestFixture::IBase>::value &&
            std::numeric_limits<typename TestFixture::IBase>::digits % 2)
        {
            EXPECT_EQ(this->baseMin, this->ipowWrapper(-this->baseTwo, this->expDigits));
        }
    });
}

TYPED_TEST(TestIPow, TestIPowNegativePower)
{
    cpp::static_if<std::is_signed<typename TestFixture::IExp>::value>
    ([&](auto) {
        for (auto exp : this->expsNegative)
        {
            for (auto base : this->basesPositive)
            {
                if (base > this->baseOne)
                {
                    EXPECT_ANY_THROW(this->ipowWrapper(base, exp));
                }
            }
            cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
            ([&](auto) {
                for (auto base : this->basesNegative)
                {
                    if (base < -this->baseOne)
                    {
                        EXPECT_ANY_THROW(this->ipowWrapper(base, exp));
                    }
                }
            });
        }
    });
}

TYPED_TEST(TestIPow, TestIPowTooLarge)
{
    for (auto base : this->basesPositive)
    {
        if (base > this->baseOne)
        {
            EXPECT_ANY_THROW(this->ipowWrapper(base, this->expDigits));
        }
    }
    cpp::static_if<std::is_signed<typename TestFixture::IBase>::value>
    ([&](auto) {
        for (auto base : this->basesNegative)
        {
            if(base < -this->baseOne)
                EXPECT_ANY_THROW(this->ipowWrapper(base, this->expDigits + 1));
            if (base < -this->baseTwo)
                EXPECT_ANY_THROW(this->ipowWrapper(base, this->expDigits));
        }
    });
    
}
