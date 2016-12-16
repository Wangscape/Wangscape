#include "NoiseMap.h"

NoiseMapBase::NoiseMapBase()
{
}

NoiseMapBase::NoiseMapBase(Bounds bounds)
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

NoiseMapVector::NoiseMapVector(size_t x, size_t y) :
    mSizeX(x), mSizeY(y), mData(x*y)
{
}

NoiseMapVector::NoiseMapVector(size_t x, size_t y, NoiseMapBase::Bounds bounds) :
    NoiseMapBase(bounds),
    mSizeX(x), mSizeY(y)
{
}

NoiseMapVector::NoiseMapVector(size_t x, size_t y, NoiseMapBase::Bounds bounds, const NoiseModule & module) :
    NoiseMapBase(bounds),
    mSizeX(x), mSizeY(y)
{
    build(module);
}

size_t NoiseMapVector::sizeX() const
{
    return mSizeX;
}

size_t NoiseMapVector::sizeY() const
{
    return mSizeY;
}

NoiseMapBase::Real NoiseMapVector::get(size_t x, size_t y) const
{
    return mData[index(x, y)];
}

void NoiseMapVector::set(size_t x, size_t y, Real value)
{
    mData[index(x, y)] = value;
}

size_t NoiseMapVector::index(size_t x, size_t y) const
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
    sf::Uint8 v = int((value + 1)*255. / 2.);
    return Colour(v, v, v, 255);
}

void NoiseMapImage::set(size_t x, size_t y, Real value)
{
    mImage.setPixel(x, y, makeColour(value));
}
