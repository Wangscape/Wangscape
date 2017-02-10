#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Cylinders>>
{
    using CylindersWrapper = noise::module::Wrapper<noise::module::Cylinders>;
    static codec::object_t<CylindersWrapper> codec();
};
}
}
