#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Clamp>>
{
    using ClampWrapper = noise::module::Wrapper<noise::module::Clamp>;
    static codec::object_t<ClampWrapper> codec()
    {
        auto codec = codec::object<ClampWrapper>();
        codec.required("type", codec::eq<std::string>("Clamp"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Bounds",
                       [](const ClampWrapper& mw) {return std::pair<double, double>(
                           mw.module.GetLowerBound(),
                           mw.module.GetUpperBound()); },
                       [](ClampWrapper& mw, std::pair<double, double> bounds) {mw.module.SetBounds(bounds.first, bounds.second); },
                       default_codec<std::pair<double, double>>());
        return codec;
    }
};
}
}
