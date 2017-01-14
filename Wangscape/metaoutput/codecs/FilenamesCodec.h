#pragma once

#include <spotify/json.hpp>

#include "metaoutput/Filenames.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<metaoutput::Filenames>
{
    static codec::object_t<metaoutput::Filenames> codec()
    {
        auto codec = codec::object<metaoutput::Filenames>();
        codec.required("TileData", &metaoutput::Filenames::tileDataFilename);
        codec.required("TileGroups", &metaoutput::Filenames::tileGroupsFilename);
        codec.required("TilesetData", &metaoutput::Filenames::tilesetDataFilename);
        codec.required("TerrainHypergraph", &metaoutput::Filenames::terrainHypergraphFilename);

        return codec;
    }
};

}
}
