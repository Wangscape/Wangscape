#pragma once

#include "CheckerboardWrapperCodec.h"

namespace spotify
{
namespace json
{

using CheckerboardWrapper = noise::module::Wrapper<noise::module::Checkerboard>;

codec::object_t<CheckerboardWrapper> default_codec_t<CheckerboardWrapper>::codec()
    {
        auto codec = codec::object<CheckerboardWrapper>();
        codec.required("type", codec::eq<std::string>("Checkerboard"));
        return codec;
    }

}
}
