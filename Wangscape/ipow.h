#pragma once
#include <type_traits>
#include <stdexcept>
#include <static_if.hpp>

namespace
{

template<typename IBase, typename IExp>
IBase ipow_imp(IBase base, IExp exp)
{
    constexpr IExp zero(0);
    constexpr IExp two(2);
    IBase result(1);
    while(exp != zero)
    {
        if (exp % two)
            result *= base;
        exp /= two;
        base *= base;
    }
    return result;
}

}

// Calculates base raised to the power of exp,
// where base and exp share an integral type.
//
// Requires:
// is_integral for IBase and IExp
// is_arithmetic for IBase and IExp
// numeric_limits for IBase
// is_signed for IBase and IExp
// IBase and IExp must be constructible from int
// numeric_limits<IBase>::digits must be representable in IExp
// Operations used:
//   Comparison operators
//   IBase *= IBase
//   IExp /= IExp
//   IExp % IExp
//   IBase << IExp
//
// Returns a correct result for all argument pairs
// that have an integer result representable in IBase.
// This includes:
// ipow(x, 0) == 0
// ipow(0, x) == 0 when x >= 0
// ipow(1, x) == 1
// ipow(-1, x) == +-1
// ipow(-2, digits) == min when digits is odd
// Some obvious failure cases raise exceptions:
// ipow(x, y) when |x| != 1 and y < 0
// ipow(x, y) when x >= 2 and y >= digits
// ipow(-2, y) when y > digits
// ipow(x, y) when x < 2 and y >= digits
// However, all other behaviour when the result
// is not an integer or is not representable in IBase
// is undefined.
// In particular, cases like ipow(digits-1, digits-1)
// are not checked, and may return nonsense results.
template <typename IBase, typename IExp, bool UseBitshift = true>
IBase ipow(IBase base, IExp exp)
{
    static_assert(std::is_integral<IBase>::value,
                  "IBase must be an integral type");
    static_assert(std::is_integral<IExp>::value,
                  "IExp must be an integral type");
    static_assert(std::is_arithmetic<IBase>::value,
                  "IBase must be an arithmetic type");
    static_assert(std::is_arithmetic<IExp>::value,
                  "IExp must be an arithmetic type");

    constexpr IExp exp_zero(0);
    constexpr IExp exp_two(2);
    constexpr IExp exp_digits = static_cast<IExp>(std::numeric_limits<IBase>::digits);
    constexpr IBase base_zero(0);
    constexpr IBase base_one(1);
    constexpr IBase base_two(2);

    if (exp == exp_zero)
        return base_one;
    if (base == base_one)
        return base_one;

    bool stop = false;
    IBase result;

    cpp::static_if<std::is_signed<IBase>::value>([&](auto)
    {
        if (base == -base_one)
        {
            stop = true;
            result = exp % exp_two ? -base_one : base_one;
        }
    });
    if (stop)
        return result;

    cpp::static_if<std::is_signed<IExp>::value>([&](auto)
    {
        if(exp < exp_zero)
            throw std::domain_error("Integer pow() with exp < 0 and |base| != 1");
    });

    if (base == base_zero)
        return base_zero;

    cpp::static_if<std::is_signed<IBase>::value>([&](auto)
    {
        if (exp > exp_digits)
            throw std::range_error("Integer pow() with exp > digits and |base| > 1");
        if (base == -base_two)
        {
            stop = true;
            cpp::static_if<UseBitshift>
            ([&](auto) {
                result = ((exp % exp_two) ? -base_one : base_one) << exp;
            })
            .else_
            ([&](auto) {
                result = ipow_imp(base, exp);
            });
        }
    });
    if (stop)
        return result;

    if (exp >= exp_digits)
        throw std::range_error("Integer pow() with exp >= digits and base not in {-2, -1, 0, 1}");
    if (base == base_two)
    {
        cpp::static_if<UseBitshift>
        ([&](auto) {
            result = base_one << exp;
        })
        .else_
        ([&](auto) {
            result = ipow_imp(base, exp);
        });
    }

    return ipow_imp(base, exp);
}
