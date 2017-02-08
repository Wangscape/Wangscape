#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Pow.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Pow>>
{
    using PowWrapper = noise::module::Wrapper<noise::module::Pow>;
    static codec::object_t<PowWrapper> codec()
    {
        auto codec = codec::object<PowWrapper>();
        codec.required("type", codec::eq<std::string>("Pow"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Exponent",
                       [](const PowWrapper& mw) {return mw.module->GetExponent(); },
                       [](PowWrapper& mw, double exponent) {mw.module->SetExponent(exponent); });
        return codec;
    }
};
}
}
