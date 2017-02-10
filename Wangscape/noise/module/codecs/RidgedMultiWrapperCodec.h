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
struct default_codec_t<noise::module::Wrapper<noise::module::RidgedMulti>>
{
    using RidgedMultiWrapper = noise::module::Wrapper<noise::module::RidgedMulti>;
    static codec::object_t<RidgedMultiWrapper> codec();
};

}
}
