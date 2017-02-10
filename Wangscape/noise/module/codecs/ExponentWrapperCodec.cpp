#pragma once

#include "ExponentWrapperCodec.h"

namespace spotify
{
namespace json
{

using ExponentWrapper = noise::module::Wrapper<noise::module::Exponent>;

codec::object_t<ExponentWrapper> default_codec_t<ExponentWrapper>::codec()
    {
        auto codec = codec::object<ExponentWrapper>();
        codec.required("type", codec::eq<std::string>("Exponent"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Exponent",
                       [](const ExponentWrapper& mw) {return mw.module->GetExponent(); },
                       [](ExponentWrapper& mw, double exponent) {mw.module->SetExponent(exponent); });
        return codec;
    }

}
}
