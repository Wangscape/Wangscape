#include "RasterValues.h"

namespace noise {

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y) :
    mSizeX(x), mSizeY(y), mData(x*y)
{
}

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y, RasterBase::Bounds bounds) :
    RasterBase(bounds),
    mSizeX(x), mSizeY(y),
    mData(x*y)
{
}

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y, RasterBase::Bounds bounds, const NoiseModule & module) :
    RasterBase(bounds),
    mSizeX(x), mSizeY(y),
    mData(x*y)
{
    build(module);
}
template<typename T>
size_t RasterValues<T>::sizeX() const
{
    return mSizeX;
}

template<typename T>
size_t RasterValues<T>::sizeY() const
{
    return mSizeY;
}

template<typename T>
T RasterValues<T>::get(size_t x, size_t y) const
{
    return mData[index(x, y)];
}

template<typename T>
void RasterValues<T>::set(size_t x, size_t y, Real value)
{
    mData[index(x, y)] = (T)value;
}

template<typename T>
size_t RasterValues<T>::index(size_t x, size_t y) const
{
    if (x >= mSizeX || y >= mSizeY)
        throw std::out_of_range("Tried to access NoiseMap with x or y out of bounds");
    return y*mSizeX + x;
}

template class RasterValues<float>;

} // namespace noise
