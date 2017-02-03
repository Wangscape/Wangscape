#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Blend>>
{
    using BlendWrapper = noise::module::Wrapper<noise::module::Blend>;
    static codec::object_t<BlendWrapper> codec()
    {
        auto codec = codec::object<BlendWrapper>();
        codec.required("type", codec::eq<std::string>("Blend"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.required("ControlModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
