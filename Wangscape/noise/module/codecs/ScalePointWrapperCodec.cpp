#pragma once

#include "ScalePointWrapperCodec.h"

namespace spotify
{
namespace json
{

using ScalePointWrapper = noise::module::Wrapper<noise::module::ScalePoint>;

codec::object_t<ScalePointWrapper> default_codec_t<ScalePointWrapper>::codec()
    {
        auto codec = codec::object<ScalePointWrapper>();
        codec.required("type", codec::eq<std::string>("ScalePoint"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XScale",
                       [](const ScalePointWrapper& mw) {return mw.module->GetXScale(); },
                       [](ScalePointWrapper& mw, double x_scale) {mw.module->SetXScale(x_scale); });
        codec.optional("YScale",
                       [](const ScalePointWrapper& mw) {return mw.module->GetYScale(); },
                       [](ScalePointWrapper& mw, double y_scale) {mw.module->SetYScale(y_scale); });
        codec.optional("ZScale",
                       [](const ScalePointWrapper& mw) {return mw.module->GetZScale(); },
                       [](ScalePointWrapper& mw, double z_scale) {mw.module->SetZScale(z_scale); });
        codec.optional("Scale",
                       [](const ScalePointWrapper& mw) {return noise::module::UniformTriple(
                           mw.module->GetXScale(),
                           mw.module->GetYScale(),
                           mw.module->GetZScale()); },
                       [](ScalePointWrapper& mw, noise::module::UniformTriple scale) {mw.module->SetScale(
                           scale.x, scale.y, scale.z); },
                       default_codec<noise::module::UniformTriple>());
        return codec;
    }

}
}
