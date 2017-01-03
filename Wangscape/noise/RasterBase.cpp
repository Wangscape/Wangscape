#include "RasterBase.h"

namespace noise {

RasterBase::RasterBase(Bounds bounds):
    mBounds(bounds)
{
}

const RasterBase::Bounds & RasterBase::bounds() const
{
    return mBounds;
}

RasterBase::Bounds & RasterBase::bounds()
{
    return mBounds;
}

void RasterBase::build(const module::Module & module)
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

} // namespace noise
