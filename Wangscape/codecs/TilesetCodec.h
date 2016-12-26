#pragma once

#include <spotify/json.hpp>

#include "Tileset.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<Tileset>
{
    static object_t<Tileset> codec()
    {
        auto codec = object<Tileset>();
        codec.required("resolution", &Tileset::resolution);
        codec.required("filename", &Tileset::filename);
        codec.required("x", &Tileset::x);
        codec.required("y", &Tileset::y);
        codec.required("terrains", &Tileset::terrains);
        return codec;
    }
};

}
}
