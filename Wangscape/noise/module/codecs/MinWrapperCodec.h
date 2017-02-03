#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Min>>
{
    using MinWrapper = noise::module::Wrapper<noise::module::Min>;
    static codec::object_t<MinWrapper> codec()
    {
        auto codec = codec::object<MinWrapper>();
        codec.required("type", codec::eq<std::string>("Min"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
