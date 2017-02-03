#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Checkerboard>>
{
    using CheckerboardWrapper = noise::module::Wrapper<noise::module::Checkerboard>;
    static codec::object_t<CheckerboardWrapper> codec()
    {
        auto codec = codec::object<CheckerboardWrapper>();
        codec.required("type", codec::eq<std::string>("Checkerboard"));
        return codec;
    }
};
}
}
