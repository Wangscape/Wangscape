#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Logarithm.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Logarithm>>
{
    using LogarithmWrapper = noise::module::Wrapper<noise::module::Logarithm>;
    static codec::object_t<LogarithmWrapper> codec();
};
}
}
