#pragma once

#include <spotify/json.hpp>

#include "TerrainSpec.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TerrainSpec>
{
    static object_t<TerrainSpec> codec()
    {
        auto codec = object<TerrainSpec>();
        codec.required("FullName", &TerrainSpec::fullName);
        codec.required("FileName", &TerrainSpec::fileName);
        codec.required("OffsetX", &TerrainSpec::offsetX);
        codec.required("OffsetY", &TerrainSpec::offsetY);

        return codec;
    }
};

}
}
