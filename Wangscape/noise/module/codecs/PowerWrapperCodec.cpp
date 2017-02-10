#pragma once

#include "PowerWrapperCodec.h"

namespace spotify
{
namespace json
{

using PowerWrapper = noise::module::Wrapper<noise::module::Power>;

codec::object_t<PowerWrapper> default_codec_t<PowerWrapper>::codec()
    {
        auto codec = codec::object<PowerWrapper>();
        codec.required("type", codec::eq<std::string>("Power"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
