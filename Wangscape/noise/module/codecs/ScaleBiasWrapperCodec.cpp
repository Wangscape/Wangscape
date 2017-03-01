#pragma once

#include "ScaleBiasWrapperCodec.h"

namespace spotify
{
namespace json
{

using ScaleBiasWrapper = noise::module::Wrapper<noise::module::ScaleBias>;

codec::object_t<ScaleBiasWrapper> default_codec_t<ScaleBiasWrapper>::codec()
    {
        auto codec = codec::object<ScaleBiasWrapper>();
        codec.required("type", codec::eq<std::string>("ScaleBias"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Scale",
                       [](const ScaleBiasWrapper& mw) {return mw.module->GetScale(); },
                       [](ScaleBiasWrapper& mw, double scale) {mw.module->SetScale(scale); });
        codec.optional("Bias",
                       [](const ScaleBiasWrapper& mw) {return mw.module->GetBias(); },
                       [](ScaleBiasWrapper& mw, double bias) {mw.module->SetBias(bias); });
        return codec;
    }

}
}
