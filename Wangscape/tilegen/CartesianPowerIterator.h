#pragma once
#include <vector>
#include <iterator>
#include <algorithm>

namespace tilegen
{
template<typename InputIt>
class CartesianPowerIterator : public std::iterator<std::input_iterator_tag,
                                                    std::vector<InputIt>>
{
public:
    const InputIt first;
    const InputIt last;

    CartesianPowerIterator(InputIt first_, InputIt last_, InputIt init, size_t power);
    CartesianPowerIterator& operator++();
    bool operator==(const CartesianPowerIterator& other) const;
    bool operator!=(const CartesianPowerIterator& other) const;
    const value_type& operator*() const;
    const InputIt& get(size_t n) const;
    const typename InputIt::difference_type coordinate(size_t n) const;
private:
    std::vector<InputIt> mComponents;
};

template<typename InputIt>
inline CartesianPowerIterator<InputIt>::CartesianPowerIterator(InputIt first_, InputIt last_, InputIt init, size_t power) :
    first(first_), last(last_),
    mComponents(power, init)
{
}

template<typename InputIt>
inline CartesianPowerIterator<typename InputIt> & CartesianPowerIterator<typename InputIt>::operator++()
{
    size_t i = 0;
    while (true)
    {
        ++mComponents[i];
        if (mComponents[i] == last && i < mComponents.size() - 1)
        {
            mComponents[i] = first;
            i++;
            continue;
        }
        break;
    }
    return *this;
}

template<typename InputIt>
inline bool CartesianPowerIterator<typename InputIt>::operator==(const CartesianPowerIterator & other) const
{
    if (first != other.first)
        return false; // different ranges
    if (last != other.last)
        return false; // different ranges
    if (mComponents.size() != (*other).size())
        return false; // different powers
    if (*mComponents.crbegin() == last && *(*other).crbegin() == last)
        return true; // both are cend
    for (size_t i = 0; i < mComponents.size(); i++)
        if (get(i) != other.get(i))
            return false; // different phases
    return true;
}

template<typename InputIt>
inline bool CartesianPowerIterator<InputIt>::operator!=(const CartesianPowerIterator & other) const
{
    return !(*this == other);
}

template<typename InputIt>
inline const typename CartesianPowerIterator<InputIt>::value_type & CartesianPowerIterator<InputIt>::operator*() const
{
    return mComponents;
}

template<typename InputIt>
inline const InputIt & CartesianPowerIterator<InputIt>::get(size_t n) const
{
    return mComponents[n];
}

template<typename InputIt>
inline const typename InputIt::difference_type CartesianPowerIterator<InputIt>::coordinate(size_t n) const
{
    return std::distance(first, mComponents[n]);
}

} // namespace tilegen
