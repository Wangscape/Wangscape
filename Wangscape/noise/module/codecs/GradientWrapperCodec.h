#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Gradient.h"
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::GradientX>>
{
    using GradientXWrapper = noise::module::Wrapper<noise::module::GradientX>;
    static codec::object_t<GradientXWrapper> codec();
};

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::GradientY>>
{
    using GradientYWrapper = noise::module::Wrapper<noise::module::GradientY>;
    static codec::object_t<GradientYWrapper> codec();
};

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::GradientZ>>
{
    using GradientZWrapper = noise::module::Wrapper<noise::module::GradientZ>;
    static codec::object_t<GradientZWrapper> codec();
};

}
}
