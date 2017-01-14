#pragma once

#include <spotify/json.hpp>

#include "TerrainSpec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TerrainSpec>
{
    static codec::object_t<TerrainSpec> codec()
    {
        auto codec = codec::object<TerrainSpec>();
        codec.required("FullName", &TerrainSpec::fullName);
        codec.required("FileName", &TerrainSpec::fileName);
        codec.required("OffsetX", &TerrainSpec::offsetX);
        codec.required("OffsetY", &TerrainSpec::offsetY);

        return codec;
    }
};

}
}
