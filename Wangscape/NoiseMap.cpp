#include "NoiseMap.h"

NoiseMapBase::NoiseMapBase()
{
}

NoiseMapBase::NoiseMapBase(Bounds bounds):
    mBounds(bounds)
{
}

const NoiseMapBase::Bounds & NoiseMapBase::bounds() const
{
    return mBounds;
}

NoiseMapBase::Bounds & NoiseMapBase::bounds()
{
    return mBounds;
}

void NoiseMapBase::build(const NoiseModule & module)
{
    Real step_x = bounds().width / sizeX();
    Real step_y = bounds().height / sizeY();
    Real start_x = bounds().left + 0.5*step_x;
    Real start_y = bounds().top + 0.5*step_y;
    for (size_t x = 0; x < sizeX(); x++)
    {
        for (size_t y = 0; y < sizeY(); y++)
        {
            set(x, y, module.GetValue(start_x + x*step_x,
                                      start_y + y*step_y,
                                      0.0));
        }
    }
}

template<typename T>
NoiseMapVector<T>::NoiseMapVector(size_t x, size_t y) :
    mSizeX(x), mSizeY(y), mData(x*y)
{
}

template<typename T>
NoiseMapVector<T>::NoiseMapVector(size_t x, size_t y, NoiseMapBase::Bounds bounds) :
    NoiseMapBase(bounds),
    mSizeX(x), mSizeY(y)
{
}

template<typename T>
NoiseMapVector<T>::NoiseMapVector(size_t x, size_t y, NoiseMapBase::Bounds bounds, const NoiseModule & module) :
    NoiseMapBase(bounds),
    mSizeX(x), mSizeY(y)
{
    build(module);
}
template<typename T>
size_t NoiseMapVector<T>::sizeX() const
{
    return mSizeX;
}

template<typename T>
size_t NoiseMapVector<T>::sizeY() const
{
    return mSizeY;
}

template<typename T>
T NoiseMapVector<T>::get(size_t x, size_t y) const
{
    return mData[index(x, y)];
}

template<typename T>
void NoiseMapVector<T>::set(size_t x, size_t y, Real value)
{
    mData[index(x, y)] = (T)value;
}

template<typename T>
size_t NoiseMapVector<T>::index(size_t x, size_t y) const
{
    if (x >= mSizeX || y >= mSizeY)
        throw std::out_of_range("Tried to access NoiseMap with x or y out of bounds");
    return y*mSizeX + x;
}

NoiseMapImage::NoiseMapImage(Image & image) :
    mImage(image)
{
}

NoiseMapImage::NoiseMapImage(Image & image, Bounds bounds) :
    mImage(image),
    NoiseMapBase(bounds)
{
}

NoiseMapImage::NoiseMapImage(Image & image, Bounds bounds, const NoiseModule & module) :
    mImage(image),
    NoiseMapBase(bounds)
{
    build(module);
}

size_t NoiseMapImage::sizeX() const
{
    return mImage.getSize().x;
}

size_t NoiseMapImage::sizeY() const
{
    return mImage.getSize().y;
}

NoiseMapImage::Colour NoiseMapImage::get(size_t x, size_t y) const
{
    return mImage.getPixel(x, y);
}

NoiseMapImage::Colour NoiseMapImage::makeColour(Real value)
{
    return Colour(std::min(255, std::max(0, int(-value * 256))),
                  0,
                  std::min(255, std::max(0, int(value * 256))),
                  255);
}

void NoiseMapImage::set(size_t x, size_t y, Real value)
{
    mImage.setPixel(x, y, makeColour(value));
}

template class NoiseMapVector<float>;