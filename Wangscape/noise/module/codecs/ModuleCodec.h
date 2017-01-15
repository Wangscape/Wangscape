#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "VoronoiCodec.h"
#include "PerlinCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Module>
{
    using Module = noise::module::Module;
    static codec::object_t<Module> codec()
    {
        auto codec = codec::one_of<
            default_codec_t<noise::module::Perlin>,
            default_codec_t<noise::module::Voronoi>>();
        return codec;
    }
};

}
}
