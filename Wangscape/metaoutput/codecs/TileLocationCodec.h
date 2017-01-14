#pragma once

#include <spotify/json.hpp>

#include "metaoutput/TileLocation.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::TileLocation>
{
    static codec::object_t<metaoutput::TileLocation> codec()
    {
        auto codec = codec::object<metaoutput::TileLocation>();
        codec.required("filename", &metaoutput::TileLocation::filename);
        codec.required("x", &metaoutput::TileLocation::x);
        codec.required("y", &metaoutput::TileLocation::y);
        return codec;
    }
};

}
}
