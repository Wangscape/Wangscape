#pragma once

#include <spotify/json.hpp>

#include "metaoutput/Tile.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::Tile>
{
    static codec::object_t<metaoutput::Tile> codec()
    {
        auto codec = codec::object<metaoutput::Tile>();
        codec.required("corners", &metaoutput::Tile::corners);
        codec.required("filename", &metaoutput::Tile::filename);
        codec.required("x", &metaoutput::Tile::x);
        codec.required("y", &metaoutput::Tile::y);
        return codec;
    }
};

}
}
