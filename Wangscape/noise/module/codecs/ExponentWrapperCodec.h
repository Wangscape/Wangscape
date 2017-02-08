#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Exponent>>
{
    using ExponentWrapper = noise::module::Wrapper<noise::module::Exponent>;
    static codec::object_t<ExponentWrapper> codec()
    {
        auto codec = codec::object<ExponentWrapper>();
        codec.required("type", codec::eq<std::string>("Exponent"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Exponent",
                       [](const ExponentWrapper& mw) {return mw.module->GetExponent(); },
                       [](ExponentWrapper& mw, double exponent) {mw.module->SetExponent(exponent); });
        return codec;
    }
};
}
}
