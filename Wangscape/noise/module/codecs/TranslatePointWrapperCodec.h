#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "UniformTripleCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::TranslatePoint>>
{
    using TranslatePointWrapper = noise::module::Wrapper<noise::module::TranslatePoint>;
    static codec::object_t<TranslatePointWrapper> codec()
    {
        auto codec = codec::object<TranslatePointWrapper>();
        codec.required("type", codec::eq<std::string>("TranslatePoint"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XTranslation",
                       [](const TranslatePointWrapper& mw) {return mw.module->GetXTranslation(); },
                       [](TranslatePointWrapper& mw, double x_translation) {mw.module->SetXTranslation(x_translation); });
        codec.optional("YTranslation",
                       [](const TranslatePointWrapper& mw) {return mw.module->GetYTranslation(); },
                       [](TranslatePointWrapper& mw, double y_translation) {mw.module->SetYTranslation(y_translation); });
        codec.optional("ZTranslation",
                       [](const TranslatePointWrapper& mw) {return mw.module->GetZTranslation(); },
                       [](TranslatePointWrapper& mw, double z_translation) {mw.module->SetZTranslation(z_translation); });
        codec.optional("Translation",
                       [](const TranslatePointWrapper& mw) {return noise::module::UniformTriple(
                           mw.module->GetXTranslation(),
                           mw.module->GetYTranslation(),
                           mw.module->GetZTranslation()); },
                       [](TranslatePointWrapper& mw, noise::module::UniformTriple translation) {mw.module->SetTranslation(
                           translation.x, translation.y, translation.z); },
                       default_codec<noise::module::UniformTriple>());
        return codec;
    }
};
}
}
