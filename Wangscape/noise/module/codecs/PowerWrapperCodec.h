#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Power>>
{
    using PowerWrapper = noise::module::Wrapper<noise::module::Power>;
    static codec::object_t<PowerWrapper> codec()
    {
        auto codec = codec::object<PowerWrapper>();
        codec.required("type", codec::eq<std::string>("Power"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
