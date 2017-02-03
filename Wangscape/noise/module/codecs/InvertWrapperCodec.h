#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Invert>>
{
    using InvertWrapper = noise::module::Wrapper<noise::module::Invert>;
    static codec::object_t<InvertWrapper> codec()
    {
        auto codec = codec::object<InvertWrapper>();
        codec.required("type", codec::eq<std::string>("Invert"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
