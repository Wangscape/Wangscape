#pragma once
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>
#include <memory>
#include "common.h"
#include "CoordinatePacker.h"

template<typename ForwardIt>
class CartesianPowerIterator;

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
    typedef std::vector<size_t> Coordinates;
    typedef const Values& reference;
    typedef const Values* pointer;

    CartesianPowerIterator(ForwardIt first_, size_t base_size_, size_t init_coordinate_, size_t power_);

    const ForwardIt& getFirst() const;
    const size_t getBaseSize() const;
    const size_t getPower() const;
    const size_t getMaxCoordinate() const;
    const size_t getMaxComponent() const;

    bool isEnd() const;

    reference getValues() const;
    const Coordinates& getCoordinates() const;

    bool operator==(const CartesianPowerIterator& other) const;
    bool operator!=(const CartesianPowerIterator& other) const;
    CartesianPowerIterator& operator++();
    CartesianPowerIterator operator++(int);
    reference operator*() const;
    pointer operator->() const;

    std::pair<size_t, size_t> coordinates2D() const;
private:
    ForwardIt mFirst;
    size_t mBaseSize;
    Iterators mIterators;
    Values mValues;
    Coordinates mCoordinates;

    const Iterators& getIterators() const;
    const ForwardIt& getIterator(size_t n) const;
    void updateValue(size_t n);
    void resetComponent(size_t n);
    void incrementComponent(size_t n);
};

template<typename ForwardIt>
inline CartesianPowerIterator<ForwardIt>::CartesianPowerIterator(ForwardIt first_, size_t base_size_, size_t init_coordinate_, size_t power_) :
    mFirst(first_), mBaseSize(base_size_),
    mCoordinates(power_, init_coordinate_)
{
    static_assert(std::is_copy_constructible<CartesianPowerIterator>::value,
                  "CartesianPowerIterator not CopyConstructible");
    static_assert(std::is_copy_assignable<CartesianPowerIterator>::value,
                  "CartesianPowerIterator not CopyAssignable");
    if (init_coordinate_ != getBaseSize())
    {
        ForwardIt init_iterator = getFirst();
        std::advance(init_iterator, init_coordinate_);
        mIterators.assign(power_, init_iterator);
        mValues.assign(power_, *init_iterator);
    }
}

template<typename ForwardIt>
inline CartesianPowerIterator<ForwardIt>& CartesianPowerIterator<ForwardIt>::operator++()
{
    for (size_t i = 0; i < getPower(); i++)
    {
        size_t coordinate = getCoordinates()[i];
        if (coordinate >= getBaseSize())
            break; // invalid or isEnd()
        if (coordinate == getMaxCoordinate())
        {
            if (i == getMaxComponent())
            {
                ++mCoordinates[i];
                break; // isEnd()
            }
            else
            {
                resetComponent(i);
            }
        }
        else
        {
            incrementComponent(i);
            break;
        }
    }
    return *this;
}

template<typename ForwardIt>
inline CartesianPowerIterator<ForwardIt> CartesianPowerIterator<ForwardIt>::operator++(int)
{
    CartesianPowerIterator previous = *this;
    ++(*this);
    return previous;
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::isEnd() const
{
    return *getCoordinates().crbegin() >= getBaseSize();
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::operator==(const CartesianPowerIterator& other) const
{
    if (getFirst() != other.getFirst())
        return false;
    if (getBaseSize() != other.getBaseSize())
        return false;
    if (getPower() != other.getPower())
        return false;
    if (isEnd() && other.isEnd())
        return true;
    return getCoordinates() == other.getCoordinates();
}

template<typename ForwardIt>
inline bool CartesianPowerIterator<ForwardIt>::operator!=(const CartesianPowerIterator& other) const
{
    return !(*this == other);
}

template<typename ForwardIt>
inline typename CartesianPowerIterator<ForwardIt>::reference CartesianPowerIterator<ForwardIt>::operator*() const
{
    return getValues();
}

template<typename ForwardIt>
inline typename CartesianPowerIterator<ForwardIt>::pointer CartesianPowerIterator<ForwardIt>::operator->() const
{
    return &getValues();
}

template<typename ForwardIt>
inline typename CartesianPowerIterator<ForwardIt>::reference CartesianPowerIterator<ForwardIt>::getValues() const
{
    return mValues;
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
inline const typename CartesianPowerIterator<ForwardIt>::Coordinates & CartesianPowerIterator<ForwardIt>::getCoordinates() const
{
    return mCoordinates;
}

template<typename ForwardIt>
inline const ForwardIt& CartesianPowerIterator<ForwardIt>::getFirst() const
{
    return mFirst;
}

template<typename ForwardIt>
inline const size_t CartesianPowerIterator<ForwardIt>::getBaseSize() const
{
    return mBaseSize;
}

template<typename ForwardIt>
inline const size_t CartesianPowerIterator<ForwardIt>::getPower() const
{
    return getCoordinates().size();
}

template<typename ForwardIt>
inline const size_t CartesianPowerIterator<ForwardIt>::getMaxCoordinate() const
{
    return getBaseSize() - 1;
}

template<typename ForwardIt>
inline const size_t CartesianPowerIterator<ForwardIt>::getMaxComponent() const
{
    return getCoordinates().size() - 1;
}

template<typename ForwardIt>
inline std::pair<size_t, size_t> CartesianPowerIterator<ForwardIt>::coordinates2D() const
{
    CoordinatePacker<size_t> x(getBaseSize());
    for (size_t i = 0; i < static_cast<size_t>(CORNERS); i += 2)
    {
        x.addCoordinate(getCoordinates()[i]);
    }
    CoordinatePacker<size_t> y(getBaseSize());
    for (size_t i = 1; i < static_cast<size_t>(CORNERS); i += 2)
    {
        y.addCoordinate(getCoordinates()[i]);
    }
    return{x.packed(), y.packed()};
}

template<typename ForwardIt>
inline void CartesianPowerIterator<ForwardIt>::updateValue(size_t n)
{
    mValues[n] = *mIterators[n];
}

template<typename ForwardIt>
inline void CartesianPowerIterator<ForwardIt>::resetComponent(size_t n)
{
    mCoordinates[n] = 0;
    mIterators[n] = getFirst();
    updateValue(n);
}

template<typename ForwardIt>
inline void CartesianPowerIterator<ForwardIt>::incrementComponent(size_t n)
{
    ++mCoordinates[n];
    ++mIterators[n];
    updateValue(n);
}

} // namespace tilegen
