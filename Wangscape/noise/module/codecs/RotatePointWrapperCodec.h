#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::RotatePoint>>
{
    using RotatePointWrapper = noise::module::Wrapper<noise::module::RotatePoint>;
    static codec::object_t<RotatePointWrapper> codec()
    {
        auto codec = codec::object<RotatePointWrapper>();
        codec.required("type", codec::eq<std::string>("RotatePoint"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XAngle",
                       [](const RotatePointWrapper& mw) {return mw.module.GetXAngle(); },
                       [](RotatePointWrapper& mw, double x_angle) {mw.module.SetXAngle(x_angle); });
        codec.optional("YAngle",
                       [](const RotatePointWrapper& mw) {return mw.module.GetYAngle(); },
                       [](RotatePointWrapper& mw, double y_angle) {mw.module.SetYAngle(y_angle); });
        codec.optional("ZAngle",
                       [](const RotatePointWrapper& mw) {return mw.module.GetZAngle(); },
                       [](RotatePointWrapper& mw, double z_angle) {mw.module.SetZAngle(z_angle); });
        return codec;
    }
};
}
}
