#pragma once

#include "InvertWrapperCodec.h"

namespace spotify
{
namespace json
{

using InvertWrapper = noise::module::Wrapper<noise::module::Invert>;

codec::object_t<InvertWrapper> default_codec_t<InvertWrapper>::codec()
    {
        auto codec = codec::object<InvertWrapper>();
        codec.required("type", codec::eq<std::string>("Invert"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
