#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Select>>
{
    using SelectWrapper = noise::module::Wrapper<noise::module::Select>;
    static codec::object_t<SelectWrapper> codec()
    {
        auto codec = codec::object<SelectWrapper>();
        codec.required("type", codec::eq<std::string>("Select"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.required("ControlModule", codec::ignore_t<int>());
        codec.optional("EdgeFalloff",
                       [](const SelectWrapper& mw) {return mw.module.GetEdgeFalloff(); },
                       [](SelectWrapper& mw, double edge_falloff) {mw.module.SetEdgeFalloff(edge_falloff); });
        codec.optional("Bounds",
                       [](const SelectWrapper& mw) {return std::pair<double, double>(
                           mw.module.GetLowerBound(),
                           mw.module.GetUpperBound()); },
                       [](SelectWrapper& mw, std::pair<double, double> bounds) {mw.module.SetBounds(bounds.first, bounds.second); },
                       default_codec<std::pair<double, double>>());
        return codec;
    }
};
}
}
