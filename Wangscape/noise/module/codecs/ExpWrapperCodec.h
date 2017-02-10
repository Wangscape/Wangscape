#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Exp.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Exp>>
{
    using ExpWrapper = noise::module::Wrapper<noise::module::Exp>;
    static codec::object_t<ExpWrapper> codec();
};
}
}
