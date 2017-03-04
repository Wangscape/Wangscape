#include "RasterImage.h"

namespace noise {

RasterImage::RasterImage(Image & image) :
    mImage(image)
{
}

RasterImage::RasterImage(Image & image, Bounds bounds) :
    mImage(image),
    RasterBase(bounds)
{
}

RasterImage::RasterImage(Image & image, Bounds bounds, const module::Module & module) :
    mImage(image),
    RasterBase(bounds)
{
    build(module);
}

size_t RasterImage::sizeX() const
{
    return mImage.getSize().x;
}

size_t RasterImage::sizeY() const
{
    return mImage.getSize().y;
}

RasterImage::Colour RasterImage::get(size_t x, size_t y) const
{
    return mImage.getPixel(x, y);
}

RasterImage::Colour RasterImage::makeColour(Real value)
{
    if (value < -1)
        return Colour(0, 255, 0);
    else if (value < 0)
        return Colour(std::min(255, std::max(0, int(-value * 256))), 0, 0);
    else if (value <= 1)
        return Colour(0, 0, std::min(255, std::max(0, int(value * 256))));
    else
        return Colour(255, 255, 255);
}

void RasterImage::set(size_t x, size_t y, Real value)
{
    mImage.setPixel(x, y, makeColour(value));
}

} // namespace noise
