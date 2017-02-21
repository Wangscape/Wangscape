#pragma once

#include <spotify/json.hpp>

#include "TileFormat.h"
#include "Vector2Codec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TileFormat>
{
    static codec::object_t<TileFormat> codec()
    {
        auto codec = codec::object<TileFormat>();
        codec.required("Resolution", &TileFormat::resolution);
        codec.required("FileType", &TileFormat::fileType);

        return codec;
    }
};

}
}
