#pragma once
#include "Vector.h"

struct CopyRegionParameters
{
    CopyRegionParameters(IVec source_origin_, IVec target_origin_, IVec size_);
    CopyRegionParameters trim(UVec source_shape, UVec target_shape);
    IVec sourceOrigin;
    IVec targetOrigin;
    IVec size;
};
