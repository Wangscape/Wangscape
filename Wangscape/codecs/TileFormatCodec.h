#pragma once

#include <spotify/json.hpp>

#include "TileFormat.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<TileFormat>
{
    static object_t<TileFormat> codec()
    {
        auto codec = object<TileFormat>();
        codec.required("Resolution", &TileFormat::resolution);
        codec.required("FileType", &TileFormat::fileType);

        return codec;
    }
};

}
}
