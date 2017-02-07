#pragma once

#include <spotify/json.hpp>

#include "BorderModuleGroupLocation.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<BorderModuleGroupLocation>
{
    static codec::object_t<BorderModuleGroupLocation> codec()
    {
        auto codec = codec::object<BorderModuleGroupLocation>();
        codec.required("Terrains", &BorderModuleGroupLocation::terrains);
        codec.required("Filename", &BorderModuleGroupLocation::filename);

        return codec;
    }
};

}
}
