#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::ScaleBias>>
{
    using ScaleBiasWrapper = noise::module::Wrapper<noise::module::ScaleBias>;
    static codec::object_t<ScaleBiasWrapper> codec()
    {
        auto codec = codec::object<ScaleBiasWrapper>();
        codec.required("type", codec::eq<std::string>("ScaleBias"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Scale",
                       [](const ScaleBiasWrapper& mw) {return mw.module.GetScale(); },
                       [](ScaleBiasWrapper& mw, double scale) {mw.module.SetScale(scale); });
        codec.optional("Bias",
                       [](const ScaleBiasWrapper& mw) {return mw.module.GetBias(); },
                       [](ScaleBiasWrapper& mw, double bias) {mw.module.SetBias(bias); });
        return codec;
    }
};
}
}
