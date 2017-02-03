#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/ModulePtr.h"
#include "NoiseQualityCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Turbulence>>
{
    using TurbulenceWrapper = noise::module::Wrapper<noise::module::Turbulence>;
    static codec::object_t<TurbulenceWrapper> codec()
    {
        auto codec = codec::object<TurbulenceWrapper>();
        codec.required("type", codec::eq<std::string>("Turbulence"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Frequency",
                       [](const TurbulenceWrapper& mw) {return mw.module.GetFrequency(); },
                       [](TurbulenceWrapper& mw, double frequency) {mw.module.SetFrequency(frequency); });
        codec.optional("Power",
                       [](const TurbulenceWrapper& mw) {return mw.module.GetPower(); },
                       [](TurbulenceWrapper& mw, double power) {mw.module.SetPower(power); });
        codec.optional("Roughness",
                       [](const TurbulenceWrapper& mw) {return mw.module.GetRoughnessCount(); },
                       [](TurbulenceWrapper& mw, int roughness) {mw.module.SetRoughness(roughness); });
        codec.optional("Seed",
                       [](const TurbulenceWrapper& mw) {return mw.module.GetSeed(); },
                       [](TurbulenceWrapper& mw, int seed) {mw.module.SetSeed(seed); });
        return codec;
    }
};

}
}
