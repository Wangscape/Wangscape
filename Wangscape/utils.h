#pragma once
#include <type_traits>
#include <stdexcept>
#include <static_if.hpp>

namespace
{

template<typename I>
I ipow_imp(I base, I exp)
{
    constexpr I zero(0);
    constexpr I two(2);
    I result(1);
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

template <typename I>
I ipow(I base, I exp)
{
    static_assert(std::is_integral<I>::value,
                  "I must be an integral type");
    if (exp == 0)
        return 1;
    if (base == 1)
        return 1;

    bool stop = false;
    I result;

    cpp::static_if<std::is_signed<I>::value>([&](auto)
    {
        if (base == -1)
        {
            stop = true;
            result = exp % 2 ? -1 : 1;
        }
    });
    if (stop)
        return result;

    cpp::static_if<std::is_signed<I>::value>([&](auto)
    {
        if(exp < 0)
            throw std::domain_error("Integer pow() with exp < 0 and |base| != 1");
    });

    if (base == 0)
        return 0;

    cpp::static_if<std::is_signed<I>::value>([&](auto)
    {
        if (exp > std::numeric_limits<I>::digits)
            throw std::range_error("Integer pow() with exp > digits and |base| > 1");
        if (base == -2)
        {
            stop = true;
            result = ((I)1 << exp) * (exp % 2 ? -1 : 1);
        }
    });
    if (stop)
        return result;

    if (exp >= std::numeric_limits<I>::digits)
        throw std::range_error("Integer pow() with exp >= digits and base not in {-2, -1, 0, 1}");
    if (base == 2)
        return (I)1 << exp;

    return ipow_imp(base, exp);
}
