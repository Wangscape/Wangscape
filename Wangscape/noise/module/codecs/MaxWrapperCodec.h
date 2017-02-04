#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Max>>
{
    using MaxWrapper = noise::module::Wrapper<noise::module::Max>;
    static codec::object_t<MaxWrapper> codec()
    {
        auto codec = codec::object<MaxWrapper>();
        codec.required("type", codec::eq<std::string>("Max"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}