#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Forward>>
{
    using ForwardWrapper = noise::module::Wrapper<noise::module::Forward>;
    static codec::object_t<ForwardWrapper> codec()
    {
        auto codec = codec::object<ForwardWrapper>();
        codec.required("type", codec::eq<std::string>("Forward"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }
};
}
}
