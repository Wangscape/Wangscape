#pragma once
#include <assert.h>

namespace tilegen
{

template<typename I>
class CoordinatePacker
{
public:
    CoordinatePacker(I size_);
    void addCoordinate(I coordinate);
    I packed() const;
    I size() const;
private:
    I mPacked;
    I mSize;
};

template<typename I>
inline CoordinatePacker<I>::CoordinatePacker(I size_) :
    mPacked(0),
    mSize(size_)
{
}

template<typename I>
inline void CoordinatePacker<I>::addCoordinate(I coordinate)
{
    if (coordinate < 0)
        throw std::domain_error("Tried to pack coordinate < 0");
    if (coordinate >= size())
        throw std::domain_error("Tried to pack coordinate > size");
    mPacked *= size();
    mPacked += coordinate;
}

template<typename I>
inline I CoordinatePacker<I>::packed() const
{
    return mPacked;
}

template<typename I>
inline I CoordinatePacker<I>::size() const
{
    return mSize;
}

} // namespace tilegen
