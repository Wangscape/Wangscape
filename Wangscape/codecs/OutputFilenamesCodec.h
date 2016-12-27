#pragma once

#include <spotify/json.hpp>

#include "OutputFilenames.h"

using namespace spotify::json::codec;

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<OutputFilenames>
{
    static object_t<OutputFilenames> codec()
    {
        auto codec = object<OutputFilenames>();
        codec.required("TileData", &OutputFilenames::tileDataFilename);
        codec.required("TileGroups", &OutputFilenames::tileGroupsFilename);
        codec.required("TilesetData", &OutputFilenames::tilesetDataFilename);
        codec.required("TerrainHypergraph", &OutputFilenames::terrainHypergraphFilename);

        return codec;
    }
};

}
}
