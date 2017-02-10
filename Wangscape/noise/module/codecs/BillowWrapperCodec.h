#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "NoiseQualityCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Billow>>
{
    using BillowWrapper = noise::module::Wrapper<noise::module::Billow>;
    static codec::object_t<BillowWrapper> codec();
};
}
}
