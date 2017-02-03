#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Add>>
{
    using AddWrapper = noise::module::Wrapper<noise::module::Add>;
    static codec::object_t<AddWrapper> codec()
    {
        auto codec = codec::object<AddWrapper>();
        codec.required("type", codec::eq<std::string>("Add"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
