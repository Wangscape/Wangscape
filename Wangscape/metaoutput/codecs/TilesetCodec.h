#pragma once

#include <spotify/json.hpp>

#include "../Tileset.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::Tileset>
{
    static object_t<metaoutput::Tileset> codec()
    {
        auto codec = object<metaoutput::Tileset>();
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
