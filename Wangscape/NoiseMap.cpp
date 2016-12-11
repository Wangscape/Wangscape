#include "NoiseMap.h"

NoiseMap::NoiseMap(size_t x, size_t y):
    mSizeX(x), mSizeY(y), mData(x*y)
{
}

NoiseMap::NoiseMap(size_t x, size_t y, NoiseMap::Bounds bounds):
    mSizeX(x), mSizeY(y), mBounds(bounds)
{
}

NoiseMap::NoiseMap(size_t x, size_t y, NoiseMap::Bounds bounds, const NoiseModule & module):
    mSizeX(x), mSizeY(y), mBounds(bounds)
{
    build(module);
}

size_t NoiseMap::getX() const
{
    return mSizeX;
}

size_t NoiseMap::getY() const
{
    return mSizeY;
}

const NoiseMap::Bounds & NoiseMap::bounds() const
{
    return mBounds;
}

NoiseMap::Bounds & NoiseMap::bounds()
{
    return mBounds;
}

void NoiseMap::build(const NoiseModule & module)
{
    Real step_x = bounds().width / getX();
    Real step_y = bounds().height / getY();
    Real start_x = bounds().left + 0.5*step_x;
    Real start_y = bounds().top + 0.5*step_y;
    for (size_t x = 0; x < getX(); x++)
    {
        for (size_t y = 0; y < getY(); y++)
        {
            mData[index(x,y)] = module.GetValue(start_x + x*step_x, start_y + y*step_y, 0.0);
        }
    }
}

NoiseMap::Real NoiseMap::get(size_t x, size_t y) const
{
    return mData[index(x, y)];
}

size_t NoiseMap::index(size_t x, size_t y) const
{
    if (x >= mSizeX || y >= mSizeY)
        throw std::out_of_range("Tried to access NoiseMap with x or y out of bounds");
    return y*mSizeX + x;
}
