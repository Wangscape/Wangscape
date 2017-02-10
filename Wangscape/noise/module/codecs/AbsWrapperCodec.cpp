#pragma once

#include "AbsWrapperCodec.h"

namespace spotify
{
namespace json
{

using AbsWrapper = noise::module::Wrapper<noise::module::Abs>;

codec::object_t<AbsWrapper> default_codec_t<AbsWrapper>::codec()
{
    auto codec = codec::object<AbsWrapper>();
    codec.required("type", codec::eq<std::string>("Abs"));
    codec.required("SourceModule", codec::ignore_t<int>());
    return codec;
}

}
}
