#pragma once

#include <spotify/json.hpp>

#include "Options.h"
#include "metaoutput/codecs/FilenamesCodec.h"
#include "TerrainSpecCodec.h"
#include "TileFormatCodec.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<Options>
{
    static object_t<Options> codec()
    {
        auto codec = object<Options>();
        codec.required("OutputDirectory", &Options::outputDirectory);
        codec.required("Terrains", &Options::terrains);
        codec.required("TileFormat", &Options::tileFormat);
        codec.required("Cliques", &Options::cliques);
        codec.required("MetaOutput", &Options::outputFilenames);

        return codec;
    }
};

}
}
