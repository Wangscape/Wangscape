#pragma once

#include <spotify/json.hpp>

#include "TerrainModuleGroupLocation.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TerrainModuleGroupLocation>
{
    static codec::object_t<TerrainModuleGroupLocation> codec()
    {
        auto codec = codec::object<TerrainModuleGroupLocation>();
        codec.required("Terrain", &TerrainModuleGroupLocation::terrain);
        codec.required("Filename", &TerrainModuleGroupLocation::filename);

        return codec;
    }
};

}
}
