#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Abs>>
{
    using AbsWrapper = noise::module::Wrapper<noise::module::Abs>;
    static codec::object_t<AbsWrapper> codec()
    {
        auto codec = codec::object<AbsWrapper>();
        codec.required("type", codec::eq<std::string>("Abs"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
