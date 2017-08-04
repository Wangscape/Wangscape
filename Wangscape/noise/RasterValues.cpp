#include "RasterValues.h"

namespace noise {

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y) :
    mData(y,x)
{
}

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y, RasterBase::Bounds bounds) :
    RasterBase(bounds),
    mData(y,x)
{
}

template<typename T>
RasterValues<T>::RasterValues(size_t x, size_t y, RasterBase::Bounds bounds, const module::Module & module) :
    RasterBase(bounds),
    mData(y,x)
{
    build(module);
}
template<typename T>
size_t RasterValues<T>::sizeX() const
{
    return mData.n_cols;
}

template<typename T>
size_t RasterValues<T>::sizeY() const
{
    return mData.n_rows;
}

template<typename T>
T RasterValues<T>::get(size_t x, size_t y) const
{
    return mData(y,x);
}

template<typename T>
void RasterValues<T>::set(size_t x, size_t y, Real value)
{
    mData(y,x) = static_cast<T>(value);
}

template class RasterValues<double>;

} // namespace noise
