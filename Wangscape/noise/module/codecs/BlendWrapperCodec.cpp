#pragma once

#include "BlendWrapperCodec.h"

namespace spotify
{
namespace json
{

using BlendWrapper = noise::module::Wrapper<noise::module::Blend>;

codec::object_t<BlendWrapper> default_codec_t<BlendWrapper>::codec()
    {
        auto codec = codec::object<BlendWrapper>();
        codec.required("type", codec::eq<std::string>("Blend"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.required("ControlModule", codec::ignore_t<int>());
        return codec;
    }

}
}
