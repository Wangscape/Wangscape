#include "RotatePointWrapperCodec.h"

namespace spotify
{
namespace json
{

using RotatePointWrapper = noise::module::Wrapper<noise::module::RotatePoint>;

codec::object_t<RotatePointWrapper> default_codec_t<RotatePointWrapper>::codec()
    {
        auto codec = codec::object<RotatePointWrapper>();
        codec.required("type", codec::eq<std::string>("RotatePoint"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("XAngle",
                       [](const RotatePointWrapper& mw) {return mw.module->GetXAngle(); },
                       [](RotatePointWrapper& mw, double x_angle) {mw.module->SetXAngle(x_angle); });
        codec.optional("YAngle",
                       [](const RotatePointWrapper& mw) {return mw.module->GetYAngle(); },
                       [](RotatePointWrapper& mw, double y_angle) {mw.module->SetYAngle(y_angle); });
        codec.optional("ZAngle",
                       [](const RotatePointWrapper& mw) {return mw.module->GetZAngle(); },
                       [](RotatePointWrapper& mw, double z_angle) {mw.module->SetZAngle(z_angle); });
        codec.optional("Angles",
                       [](const RotatePointWrapper& mw) {return std::tuple<double, double, double>(
                           mw.module->GetXAngle(),
                           mw.module->GetYAngle(),
                           mw.module->GetZAngle()); },
                       [](RotatePointWrapper& mw, std::tuple<double, double, double> angles) {mw.module->SetAngles(
                           std::get<0>(angles), std::get<1>(angles), std::get<2>(angles)); },
                       default_codec<std::tuple<double, double, double>>());
        return codec;
    }

}
}
