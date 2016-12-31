#pragma once

#include <spotify/json.hpp>

#include "../TileLocation.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::TileLocation>
{
    static object_t<metaoutput::TileLocation> codec()
    {
        auto codec = object<metaoutput::TileLocation>();
        codec.required("filename", &metaoutput::TileLocation::filename);
        codec.required("x", &metaoutput::TileLocation::x);
        codec.required("y", &metaoutput::TileLocation::y);
        return codec;
    }
};

}
}
