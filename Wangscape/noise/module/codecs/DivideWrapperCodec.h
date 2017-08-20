#pragma once

#include <spotify/json.hpp>

#include "noise/module/Divide.h"
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Divide>>
{
    using DivideWrapper = noise::module::Wrapper<noise::module::Divide>;
    static codec::object_t<DivideWrapper> codec();
};
}
}
