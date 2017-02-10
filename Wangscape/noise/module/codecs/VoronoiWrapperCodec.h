#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Voronoi>>
{
    using VoronoiWrapper = noise::module::Wrapper<noise::module::Voronoi>;
    static codec::object_t<VoronoiWrapper> codec();
};
}
}
