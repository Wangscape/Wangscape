#pragma once

#include <spotify/json.hpp>

#include "metaoutput/Tileset.h"
#include "codecs/Vector2Codec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::Tileset>
{
    static codec::object_t<metaoutput::Tileset> codec()
    {
        auto codec = codec::object<metaoutput::Tileset>();
        codec.required("resolution", &metaoutput::Tileset::resolution);
        codec.required("filename", &metaoutput::Tileset::filename);
        codec.required("x", &metaoutput::Tileset::x);
        codec.required("y", &metaoutput::Tileset::y);
        codec.required("terrains", &metaoutput::Tileset::terrains);
        return codec;
    }
};

}
}
