#pragma once
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>
#include "common.h"
#include "CoordinatePacker.h"

namespace tilegen
{
template<typename ForwardIt>
class CartesianPowerIterator : public std::iterator<std::input_iterator_tag,
                                                    std::vector<typename ForwardIt::value_type>>
{
public:
    static_assert(std::is_base_of<std::forward_iterator_tag,
                                  typename std::iterator_traits<ForwardIt>::iterator_category>::value,
                  "ForwardIt must be at least a ForwardIterator");
    typedef std::vector<typename ForwardIt::value_type> Values;
    typedef std::vector<ForwardIt> Iterators;

    CartesianPowerIterator(ForwardIt first_, ForwardIt last_, ForwardIt init_, size_t power_);

    const ForwardIt& getFirst() const;
    const ForwardIt& getLast() const;

    bool isEnd() const;

    bool operator==(const CartesianPowerIterator& other) const;
    bool operator!=(const CartesianPowerIterator& other) const;
    CartesianPowerIterator& operator++();


    const Values& getValues() const;
    const typename ForwardIt::value_type& getValue(size_t n) const;

    const Values& operator*() const;
    const typename ForwardIt::value_type& operator[](size_t n) const;

    const Iterators& getIterators() const;
    const ForwardIt& getIterator(size_t n) const;

    const typename ForwardIt::difference_type coordinate(size_t n) const;

    std::pair<size_t, size_t> coordinates_2d() const;
private:
    const ForwardIt mFirst;
    const ForwardIt mLast;
    std::vector<ForwardIt> mIterators;
    Values mValues;
};

template<typename ForwardIt>
inline CartesianPowerIterator<ForwardIt>::CartesianPowerIterator(ForwardIt first_, ForwardIt last_, ForwardIt init_, size_t power_) :
    mFirst(first_), mLast(last_),
    mIterators(power_, init_)
{
    if (init_ != last_)
        for (const auto& it : mIterators)
            mValues.push_back(*it);
}

template<typename ForwardIt>
inline CartesianPowerIterator<ForwardIt>& CartesianPowerIterator<typename ForwardIt>::operator++()
{
    for (size_t i = 0; i < mIterators.size(); i++)
    {
        ++mIterators[i];
        if (i < mIterators.size() - 1)
        {
            if (mIterators[i] == getLast())
            {
                mIterators[i] = getFirst();
                mValues[i] = *mIterators[i];
            }
            else
            {
                mValues[i] = *mIterators[i];
                break;
            }
        }
        else if (mIterators[i] != getLast())
        {
            mValues[i] = *mIterators[i];
        }
    }
    return *this;
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::isEnd() const
{
    return *getIterators().crbegin() == getLast();
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::operator==(const CartesianPowerIterator& other) const
{
    if (std::tie(getFirst(), getLast()) !=
        std::tie(other.getFirst(), other.getLast()))
    {
        return false;
    }
    if (getIterators().size() != other.getIterators().size())
        return false;
    if (isEnd() && other.isEnd())
        return true;
    return getIterators() == other.getIterators();
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::operator!=(const CartesianPowerIterator& other) const
{
    return !(*this == other);
}

template<typename ForwardIt>
inline const typename CartesianPowerIterator<ForwardIt>::Values& CartesianPowerIterator<ForwardIt>::operator*() const
{
    return getValues();
}

template<typename ForwardIt>
inline const typename ForwardIt::value_type & CartesianPowerIterator<ForwardIt>::operator[](size_t n) const
{
    return getValue(n);
}

template<typename ForwardIt>
inline const typename CartesianPowerIterator<ForwardIt>::Values & CartesianPowerIterator<ForwardIt>::getValues() const
{
    return mValues;
}

template<typename ForwardIt>
inline const typename ForwardIt::value_type& CartesianPowerIterator<ForwardIt>::getValue(size_t n) const
{
    return getValues()[n];
}

template<typename ForwardIt>
inline const typename CartesianPowerIterator<ForwardIt>::Iterators& CartesianPowerIterator<ForwardIt>::getIterators() const
{
    return mIterators;
}

template<typename ForwardIt>
inline const ForwardIt& CartesianPowerIterator<ForwardIt>::getIterator(size_t n) const
{
    return getIterators()[n];
}

template<typename ForwardIt>
inline const typename ForwardIt::difference_type CartesianPowerIterator<ForwardIt>::coordinate(size_t n) const
{
    return std::distance(getFirst(), mIterators[n]);
}

template<typename ForwardIt>
inline const ForwardIt& CartesianPowerIterator<ForwardIt>::getFirst() const
{
    return mFirst;
}

template<typename ForwardIt>
inline const ForwardIt& CartesianPowerIterator<ForwardIt>::getLast() const
{
    return mLast;
}

template<typename ForwardIt>
inline std::pair<size_t, size_t> CartesianPowerIterator<ForwardIt>::coordinates_2d() const
{
    size_t clique_size = std::distance(getFirst(), getLast());
    CoordinatePacker<size_t> x(clique_size);
    for (size_t i = 0; i < static_cast<size_t>(CORNERS); i += 2)
    {
        x.addCoordinate(coordinate(i));
    }
    CoordinatePacker<size_t> y(clique_size);
    for (size_t i = 1; i < static_cast<size_t>(CORNERS); i += 2)
    {
        y.addCoordinate(coordinate(i));
    }

    return{x.packed(), y.packed()};
}

} // namespace tilegen
