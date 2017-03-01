#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/UniformTriple.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::UniformTriple>
{
    //codec::one_of_t<
    //    codec::transform_t<noise::module::UniformTriple, codec::tuple_t<std::tuple<double, double, double>>>,
    //    codec::transform_t<noise::module::UniformTriple, codec::number_t<double>>>
    static auto codec()
    {
        auto codec_uniform = codec::transform(
            codec::number<double>(),
            [](const noise::module::UniformTriple&)
        {
            throw std::runtime_error("Cannot encode UniformTriple as single number");
            return std::numeric_limits<double>::signaling_NaN();
        },
            [](double xyz)
        {
            return noise::module::UniformTriple(xyz);
        });
        auto codec_triple = codec::transform(
            codec::tuple(codec::number<double>(), codec::number<double>(), codec::number<double>()),
            [](const noise::module::UniformTriple& xyz)
        {
            return xyz.asTuple();
        },
            [](std::tuple<double, double, double> xyz)
        {
            return noise::module::UniformTriple(xyz);
        });

        return codec::one_of(codec_triple, codec_uniform);
    }
};

}
}
