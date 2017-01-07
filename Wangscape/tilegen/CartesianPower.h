#pragma once
#include "CartesianPowerIterator.h"
#include <utility>

namespace tilegen
{

template<typename InputIt>
class CartesianPower
{
public:
    typedef CartesianPowerIterator<InputIt> const_iterator;

    CartesianPower(InputIt first_, InputIt last_, size_t power_);
    template<typename Container>
    CartesianPower(const Container& container, size_t power_);

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_iterator begin() const;
    const_iterator end() const;
    size_t size() const;

    InputIt first;
    InputIt last;
    size_t power;
};

template<typename InputIt>
inline CartesianPower<InputIt>::CartesianPower(InputIt first_, InputIt last_, size_t power_) :
    first(first_),
    last(last_),
    power(power_)
{
}

template<typename InputIt>
typename CartesianPower<InputIt>::const_iterator CartesianPower<InputIt>::cbegin() const
{
    return const_iterator(first, last, first, power);
}

template<typename InputIt>
typename CartesianPower<InputIt>::const_iterator CartesianPower<InputIt>::cend() const
{
    return const_iterator(first, last, last, power);
}

template<typename InputIt>
typename CartesianPower<InputIt>::const_iterator CartesianPower<InputIt>::begin() const
{
    return cbegin();
}

template<typename InputIt>
typename CartesianPower<InputIt>::const_iterator CartesianPower<InputIt>::end() const
{
    return cend();
}

template<typename InputIt>
inline size_t CartesianPower<InputIt>::size() const
{
    size_t base_size = std::distance(first, last);
    size_t result = 1;
    for (size_t i = 0; i < power; i++)
    {
        result *= base_size;
    }
    return result;
}

template<typename InputIt>
template<typename Container>
inline CartesianPower<InputIt>::CartesianPower(const Container & container, size_t power_) :
    CartesianPower(container.cbegin(), container.cend(), power_)
{
}

} // namespace tilegen
