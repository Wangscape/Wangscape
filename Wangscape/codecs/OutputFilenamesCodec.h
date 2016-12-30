#pragma once

#include <spotify/json.hpp>

#include "metaoutput/OutputFilenames.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::OutputFilenames>
{
    static object_t<metaoutput::OutputFilenames> codec()
    {
        auto codec = object<metaoutput::OutputFilenames>();
        codec.required("TileData", &metaoutput::OutputFilenames::tileDataFilename);
        codec.required("TileGroups", &metaoutput::OutputFilenames::tileGroupsFilename);
        codec.required("TilesetData", &metaoutput::OutputFilenames::tilesetDataFilename);
        codec.required("TerrainHypergraph", &metaoutput::OutputFilenames::terrainHypergraphFilename);

        return codec;
    }
};

}
}
