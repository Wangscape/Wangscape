#include "CopyRegionParameters.h"



CopyRegionParameters::CopyRegionParameters(IVec source_origin_, IVec target_origin_, IVec size_) :
    sourceOrigin(source_origin_), targetOrigin(target_origin_), size(size_)
{
}

CopyRegionParameters CopyRegionParameters::trim(UVec source_shape, UVec target_shape)
{
    CopyRegionParameters trimmed = *this;

    // Cut off negative indices in source or target
    IVec origin_excess;
    origin_excess.x() = std::min({sourceOrigin.x(),
                                 targetOrigin.x(),
                                 0});
    origin_excess.y() = std::min({sourceOrigin.y(),
                                 targetOrigin.y(),
                                 0});
    trimmed.sourceOrigin -= origin_excess;
    trimmed.targetOrigin -= origin_excess;
    trimmed.size += origin_excess;

    // Cut off indices greater than shape in source or target
    const auto source_end = sourceOrigin + size;
    const auto target_end = targetOrigin + size;
    IVec end_excess;
    end_excess.x() = std::max({source_end.x() - (int)source_shape.x(),
                              target_end.x() - (int)target_shape.x(),
                              0});
    end_excess.y() = std::max({source_end.y() - (int)source_shape.y(),
                              target_end.y() - (int)target_shape.y(),
                              0});
    trimmed.size -= end_excess;

    return trimmed;
}
