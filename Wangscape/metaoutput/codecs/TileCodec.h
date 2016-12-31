#pragma once

#include <spotify/json.hpp>

#include "../Tile.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::Tile>
{
    static object_t<metaoutput::Tile> codec()
    {
        auto codec = object<metaoutput::Tile>();
        codec.required("corners", &metaoutput::Tile::corners);
        codec.required("filename", &metaoutput::Tile::filename);
        codec.required("x", &metaoutput::Tile::x);
        codec.required("y", &metaoutput::Tile::y);
        return codec;
    }
};

}
}
