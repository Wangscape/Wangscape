#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/QuadrantSelector.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::QuadrantSelector>>
{
    using QuadrantSelectorWrapper = noise::module::Wrapper<noise::module::QuadrantSelector>;
    static codec::object_t<QuadrantSelectorWrapper> codec();
};
}
}
