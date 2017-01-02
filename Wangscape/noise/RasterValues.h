#pragma once
#include <vector>
#include <type_traits>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include "RasterBase.h"

namespace noise
{

template <typename T>
class RasterValues : public RasterBase
{
public:
    static_assert(std::is_convertible<Real,T>::value,
                  "T must be convertible from Real");
    typedef std::vector<T> Data;
    RasterValues(size_t x, size_t y);
    RasterValues(size_t x, size_t y, Bounds bounds);
    RasterValues(size_t x, size_t y, Bounds bounds, const NoiseModule& module);

    virtual size_t sizeX() const;
    virtual size_t sizeY() const;
    T get(size_t x, size_t y) const;
protected:
    virtual void set(size_t x, size_t y, Real value);
    size_t index(size_t x, size_t y) const;
    size_t mSizeX;
    size_t mSizeY;
    Data mData;
};

} // namespace noise
