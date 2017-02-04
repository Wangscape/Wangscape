#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Curve>>
{
    using CurveWrapper = noise::module::Wrapper<noise::module::Curve>;
    static codec::object_t<CurveWrapper> codec()
    {
        auto codec = codec::object<CurveWrapper>();
        codec.required("type", codec::eq<std::string>("Curve"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("ControlPoints",
                       [](const CurveWrapper& mw)
                       {
                           std::vector<std::pair<double, double>> all_control_points;
                           const noise::module::ControlPoint* raw_control_points = mw.module.GetControlPointArray();
                           const int control_point_count = mw.module.GetControlPointCount();
                           for (int i = 0; i < control_point_count; i++)
                           {
                               const noise::module::ControlPoint control_point = raw_control_points[i];
                               all_control_points.push_back({control_point.inputValue, control_point.outputValue});
                           }
                           return all_control_points;
                       },
                                      [](CurveWrapper& mw, std::vector<std::pair<double, double>> all_control_points)
                       {
                           for (std::pair<double, double> control_point : all_control_points)
                           {
                               mw.module.AddControlPoint(control_point.first, control_point.second);
                           }
                       },
                       default_codec<std::vector<std::pair<double, double>>>());
        return codec;
    }
};
}
}