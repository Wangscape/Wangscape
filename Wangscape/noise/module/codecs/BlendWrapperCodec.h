#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Blend>>
{
    using BlendWrapper = noise::module::Wrapper<noise::module::Blend>;
    static codec::object_t<BlendWrapper> codec();
};
}
}
