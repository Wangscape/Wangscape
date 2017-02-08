#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Terrace>>
{
    using TerraceWrapper = noise::module::Wrapper<noise::module::Terrace>;
    static codec::object_t<TerraceWrapper> codec()
    {
        auto codec = codec::object<TerraceWrapper>();
        codec.required("type", codec::eq<std::string>("Terrace"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("AllControlPoints",
                       [](const TerraceWrapper& mw)
                       {
                           std::vector<double> control_points;
                           const double* raw_control_points = mw.module->GetControlPointArray();
                           const int control_point_count = mw.module->GetControlPointCount();
                           for (int i = 0; i < control_point_count; i++)
                           {
                               control_points.push_back(raw_control_points[i]);
                           }
                           return control_points;
                       },
                       [](TerraceWrapper& mw, std::vector<double> all_control_points)
                       {
                           for (double control_point : all_control_points)
                           {
                               mw.module->AddControlPoint(control_point);
                           }
                       },
                       default_codec<std::vector<double>>());
        return codec;
    }
};
}
}
