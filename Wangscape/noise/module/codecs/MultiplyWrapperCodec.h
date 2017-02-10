#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Multiply>>
{
    using MultiplyWrapper = noise::module::Wrapper<noise::module::Multiply>;
    static codec::object_t<MultiplyWrapper> codec();
};
}
}
