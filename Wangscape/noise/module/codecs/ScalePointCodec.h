#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::ScalePoint>>
{
    using ScalePointWrapper = noise::module::Wrapper<noise::module::ScalePoint>;
    static codec::object_t<ScalePointWrapper> codec()
    {
        auto codec = codec::object<ScalePointWrapper>();
        codec.required("type", codec::eq<std::string>("ScalePoint"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XScale",
                       [](const ScalePointWrapper& mw) {return mw.module.GetXScale(); },
                       [](ScalePointWrapper& mw, double x_scale) {mw.module.SetXScale(x_scale); });
        codec.optional("YScale",
                       [](const ScalePointWrapper& mw) {return mw.module.GetYScale(); },
                       [](ScalePointWrapper& mw, double y_scale) {mw.module.SetYScale(y_scale); });
        codec.optional("ZScale",
                       [](const ScalePointWrapper& mw) {return mw.module.GetZScale(); },
                       [](ScalePointWrapper& mw, double z_scale) {mw.module.SetZScale(z_scale); });
        codec.optional("Scale",
                       [](const ScalePointWrapper& mw) {return std::tuple<double, double, double>(
                           mw.module.GetXScale(),
                           mw.module.GetYScale(),
                           mw.module.GetZScale()); },
                       [](ScalePointWrapper& mw, std::tuple<double, double, double> scale) {mw.module.SetScale(
                           std::get<0>(scale), std::get<1>(scale), std::get<2>(scale)); },
                       default_codec<std::tuple<double, double, double>>());
        return codec;
    }
};
}
}
