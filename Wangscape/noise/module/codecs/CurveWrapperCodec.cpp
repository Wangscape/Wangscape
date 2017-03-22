#include "CurveWrapperCodec.h"

namespace spotify
{
namespace json
{

using CurveWrapper = noise::module::Wrapper<noise::module::Curve>;

codec::object_t<CurveWrapper> default_codec_t<CurveWrapper>::codec()
    {
        auto codec = codec::object<CurveWrapper>();
        codec.required("type", codec::eq<std::string>("Curve"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("ControlPoints",
                       [](const CurveWrapper& mw)
                       {
                           std::vector<std::pair<double, double>> all_control_points;
                           const noise::module::ControlPoint* raw_control_points = mw.module->GetControlPointArray();
                           const int control_point_count = mw.module->GetControlPointCount();
                           std::transform(raw_control_points,
                                          raw_control_points + control_point_count,
                                          std::inserter(all_control_points, all_control_points.begin()),
                                          [](noise::module::ControlPoint control_point)
                           {
                               return std::make_pair(control_point.inputValue, control_point.outputValue);
                           });
                           return all_control_points;
                       },
                       [](CurveWrapper& mw, std::vector<std::pair<double, double>> all_control_points)
                       {
                           for (std::pair<double, double> control_point : all_control_points)
                           {
                               mw.module->AddControlPoint(control_point.first, control_point.second);
                           }
                       },
                       default_codec<std::vector<std::pair<double, double>>>());
        return codec;
    }

}
}
