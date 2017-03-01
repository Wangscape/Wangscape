#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Forward.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Forward>>
{
    using ForwardWrapper = noise::module::Wrapper<noise::module::Forward>;
    static codec::object_t<ForwardWrapper> codec();
};
}
}
