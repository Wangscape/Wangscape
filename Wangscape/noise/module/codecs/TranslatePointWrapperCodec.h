#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

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
                       [](const TranslatePointWrapper& mw) {return std::tuple<double, double, double>(
                           mw.module->GetXTranslation(),
                           mw.module->GetYTranslation(),
                           mw.module->GetZTranslation()); },
                       [](TranslatePointWrapper& mw, std::tuple<double, double, double> translation) {mw.module->SetTranslation(
                           std::get<0>(translation), std::get<1>(translation), std::get<2>(translation)); },
                       default_codec<std::tuple<double, double, double>>());
        return codec;
    }
};
}
}
