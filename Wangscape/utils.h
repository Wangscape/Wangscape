#pragma once
#include <type_traits>
#include <stdexcept>

namespace
{

template<typename I>
I _pow(I base, I exp)
{
    I result = 1;
    for (int i = 0; i < std::numeric_limits<I>::digits; i++)
    {
        if (exp & 1)
            result *= base;
        else if (exp == 0)
            break;
        exp >>= 1;
        base *= base;
    }
    return result;
}

}

template <typename I>
typename std::enable_if<std::is_unsigned<I>::value, I>::type pow(I base, I exp)
{
    if (exp == 0)
        return 1;
    else if (base == 0)
        return 0;
    else if (base == 1)
        return 1;
    else if (exp >= std::numeric_limits<I>::digits)
        throw std::range_error("Integer pow() with exp >= digits and base > 1");
    else if (base == 2)
        return (I)1 << exp;
    return _pow(base, exp);
}

template <typename I>
typename std::enable_if<!std::is_unsigned<I>::value, I>::type pow(I base, I exp)
{
    if (exp == 0)
        return 1;
    else if (base == 1)
        return 1;
    else if (base == -1)
        return exp % 2 ? -1 : 1;
    else if (exp < 0)
        throw std::domain_error("Integer pow() with exp < 0 and |base| != 1");
    else if (base == 0)
        return 0;
    else if (exp > std::numeric_limits<I>::digits)
        throw std::range_error("Integer pow() with exp > digits and |base| > 1");
    else if (base == -2)
        return ((I)1 << exp) * (exp % 2 ? -1 : 1);
    else if (exp >= std::numeric_limits<I>::digits)
        throw std::range_error("Integer pow() with exp >= digits and base not in {-2, -1, 0, 1}");
    else if (base == 2)
        return (I)1 << exp;
    return _pow(base, exp);
}
