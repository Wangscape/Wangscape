#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Voronoi>>
{
    using VoronoiWrapper = noise::module::Wrapper<noise::module::Voronoi>;
    static codec::object_t<VoronoiWrapper> codec()
    {
        auto codec = codec::object<VoronoiWrapper>();
        codec.required("type", codec::eq<std::string>("Voronoi"));
        codec.optional("Frequency",
                       [](const VoronoiWrapper& mw) {return mw.module->GetFrequency(); },
                       [](VoronoiWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        codec.optional("Displacement",
                       [](const VoronoiWrapper& mw) {return mw.module->GetDisplacement(); },
                       [](VoronoiWrapper& mw, double displacement) {mw.module->SetDisplacement(displacement); });
        codec.optional("DistanceEnabled",
                       [](const VoronoiWrapper& mw) {return mw.module->IsDistanceEnabled(); },
                       [](VoronoiWrapper& mw, bool distance_enabled) {mw.module->EnableDistance(distance_enabled); });
        codec.optional("Seed",
                       [](const VoronoiWrapper& mw) {return mw.module->GetSeed(); },
                       [](VoronoiWrapper& mw, int seed) {mw.module->SetSeed(seed); });
        return codec;
    }
};
}
}
