#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Cylinders>>
{
    using CylindersWrapper = noise::module::Wrapper<noise::module::Cylinders>;
    static codec::object_t<CylindersWrapper> codec()
    {
        auto codec = codec::object<CylindersWrapper>();
        codec.required("type", codec::eq<std::string>("Cylinders"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Frequency",
                       [](const CylindersWrapper& mw) {return mw.module->GetFrequency(); },
                       [](CylindersWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        return codec;
    }
};
}
}
