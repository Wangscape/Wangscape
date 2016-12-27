#pragma once

#include <spotify/json.hpp>

#include "TileLocation.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TileLocation>
{
    static object_t<TileLocation> codec()
    {
        auto codec = object<TileLocation>();
        codec.required("filename", &TileLocation::filename);
        codec.required("x", &TileLocation::x);
        codec.required("y", &TileLocation::y);
        return codec;
    }
};

}
}
