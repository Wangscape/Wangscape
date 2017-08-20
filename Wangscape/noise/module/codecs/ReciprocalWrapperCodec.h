#pragma once

#include <spotify/json.hpp>

#include "noise/module/Reciprocal.h"
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Reciprocal>>
{
    using ReciprocalWrapper = noise::module::Wrapper<noise::module::Reciprocal>;
    static codec::object_t<ReciprocalWrapper> codec();
};
}
}
