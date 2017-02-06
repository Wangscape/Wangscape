#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/QuadrantSelector.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::QuadrantSelector>>
{
    using QuadrantSelectorWrapper = noise::module::Wrapper<noise::module::QuadrantSelector>;
    static codec::object_t<QuadrantSelectorWrapper> codec()
    {
        auto codec = codec::object<QuadrantSelectorWrapper>();
        codec.required("type", codec::eq<std::string>("QuadrantSelector"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XTranslate",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslate(0); },
                       [](QuadrantSelectorWrapper& mw, bool x_translate) {mw.module.SetTranslate(0, x_translate); });
        codec.optional("YTranslate",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslate(1); },
                       [](QuadrantSelectorWrapper& mw, bool y_translate) {mw.module.SetTranslate(1, y_translate); });
        codec.optional("ZTranslate",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslate(2); },
                       [](QuadrantSelectorWrapper& mw, bool z_translate) {mw.module.SetTranslate(2, z_translate); });
        codec.optional("Translate",
                       [](const QuadrantSelectorWrapper& mw) {return std::tuple<bool, bool, bool>(
                           mw.module.GetTranslate(0),
                           mw.module.GetTranslate(1),
                           mw.module.GetTranslate(2)); },
                       [](QuadrantSelectorWrapper& mw, std::tuple<bool, bool, bool> translate) {mw.module.SetTranslate(
                           std::get<0>(translate), std::get<1>(translate), std::get<2>(translate)); },
                       default_codec<std::tuple<bool, bool, bool>>());
        codec.optional("XTranslateIgnored",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslateIgnored(0); },
                       [](QuadrantSelectorWrapper& mw, bool x_translate_ignored) {mw.module.SetTranslateIgnored(0, x_translate_ignored); });
        codec.optional("YTranslateIgnored",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslateIgnored(1); },
                       [](QuadrantSelectorWrapper& mw, bool y_translate_ignored) {mw.module.SetTranslateIgnored(1, y_translate_ignored); });
        codec.optional("ZTranslateIgnored",
                       [](const QuadrantSelectorWrapper& mw) {return mw.module.GetTranslateIgnored(2); },
                       [](QuadrantSelectorWrapper& mw, bool z_translate_ignored) {mw.module.SetTranslateIgnored(2, z_translate_ignored); });
        codec.optional("TranslateIgnored",
                       [](const QuadrantSelectorWrapper& mw) {return std::tuple<bool, bool, bool>(
                           mw.module.GetTranslateIgnored(0),
                           mw.module.GetTranslateIgnored(1),
                           mw.module.GetTranslateIgnored(2)); },
                       [](QuadrantSelectorWrapper& mw, std::tuple<bool, bool, bool> translate_ignored) {mw.module.SetTranslateIgnored(
                           std::get<0>(translate_ignored), std::get<1>(translate_ignored), std::get<2>(translate_ignored)); },
                       default_codec<std::tuple<bool, bool, bool>>());
        return codec;
    }
};
}
}
