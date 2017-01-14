#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>

#include "NoiseQualityCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Voronoi>
{
    using Voronoi = noise::module::Voronoi;
    static codec::object_t<Voronoi> codec()
    {
        auto codec = codec::object<Voronoi>();
        codec.required("type", codec::eq<std::string>("Voronoi"));
        codec.optional("Frequency",
                       &Voronoi::GetFrequency,
                       &Voronoi::SetFrequency);
        codec.optional("Displacement",
                       &Voronoi::GetDisplacement,
                       &Voronoi::SetDisplacement);
        codec.optional("DistanceEnabled",
                       &Voronoi::IsDistanceEnabled,
                       &Voronoi::EnableDistance);
        codec.optional("Seed",
                       &Voronoi::GetSeed,
                       &Voronoi::SetSeed);

        return codec;
    }
};

}
}
