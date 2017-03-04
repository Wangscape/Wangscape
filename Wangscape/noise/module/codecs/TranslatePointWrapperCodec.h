#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "UniformTripleCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::TranslatePoint>>
{
    using TranslatePointWrapper = noise::module::Wrapper<noise::module::TranslatePoint>;
    static codec::object_t<TranslatePointWrapper> codec();
};
}
}
