#pragma once

#include <spotify/json.hpp>

#include "Tile.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<Tile>
{
    static object_t<Tile> codec()
    {
        auto codec = object<Tile>();
        codec.required("corners", &Tile::corners);
        codec.required("filename", &Tile::filename);
        codec.required("x", &Tile::x);
        codec.required("y", &Tile::y);
        return codec;
    }
};

}
}
