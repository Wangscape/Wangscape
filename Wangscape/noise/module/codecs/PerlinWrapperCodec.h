#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/ModulePtr.h"
#include "NoiseQualityCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Perlin>>
{
    using PerlinWrapper = noise::module::Wrapper<noise::module::Perlin>;
    static codec::object_t<PerlinWrapper> codec();
};

}
}
