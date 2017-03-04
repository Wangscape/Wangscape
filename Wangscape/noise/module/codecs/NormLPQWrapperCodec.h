#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/NormLPQ.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::NormLPQ>>
{
    using NormLPQWrapper = noise::module::Wrapper<noise::module::NormLPQ>;
    static codec::object_t<NormLPQWrapper> codec();
};
}
}
