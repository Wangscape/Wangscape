#pragma once

#include "GradientWrapperCodec.h"

namespace spotify
{
namespace json
{

using GradientXWrapper = noise::module::Wrapper<noise::module::GradientX>;

codec::object_t<GradientXWrapper> default_codec_t<GradientXWrapper>::codec()
    {
        auto codec = codec::object<GradientXWrapper>();
        codec.required("type", codec::eq<std::string>("GradientX"));
        return codec;
    }

using GradientYWrapper = noise::module::Wrapper<noise::module::GradientY>;

codec::object_t<GradientYWrapper> default_codec_t<GradientYWrapper>::codec()
    {
        auto codec = codec::object<GradientYWrapper>();
        codec.required("type", codec::eq<std::string>("GradientY"));
        return codec;
    }

using GradientZWrapper = noise::module::Wrapper<noise::module::GradientZ>;

codec::object_t<GradientZWrapper> default_codec_t<GradientZWrapper>::codec()
    {
        auto codec = codec::object<GradientZWrapper>();
        codec.required("type", codec::eq<std::string>("GradientZ"));
        return codec;
    }

}
}
