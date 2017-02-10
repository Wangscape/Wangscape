#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/CornerCombinerBase.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::CornerCombinerBase>>
{
    using CornerCombinerBaseWrapper = noise::module::Wrapper<noise::module::CornerCombinerBase>;
    static codec::object_t<CornerCombinerBaseWrapper> codec();
};
}
}
