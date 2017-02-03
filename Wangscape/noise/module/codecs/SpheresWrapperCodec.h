#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Spheres>>
{
    using SpheresWrapper = noise::module::Wrapper<noise::module::Spheres>;
    static codec::object_t<SpheresWrapper> codec()
    {
        auto codec = codec::object<SpheresWrapper>();
        codec.required("type", codec::eq<std::string>("Spheres"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Frequency",
                       [](const SpheresWrapper& mw) {return mw.module.GetFrequency(); },
                       [](SpheresWrapper& mw, double frequency) {mw.module.SetFrequency(frequency); });
        return codec;
    }
};
}
}
