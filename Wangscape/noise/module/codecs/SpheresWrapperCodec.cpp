#pragma once

#include "SpheresWrapperCodec.h"

namespace spotify
{
namespace json
{

using SpheresWrapper = noise::module::Wrapper<noise::module::Spheres>;

codec::object_t<SpheresWrapper> default_codec_t<SpheresWrapper>::codec()
    {
        auto codec = codec::object<SpheresWrapper>();
        codec.required("type", codec::eq<std::string>("Spheres"));
        codec.optional("Frequency",
                       [](const SpheresWrapper& mw) {return mw.module->GetFrequency(); },
                       [](SpheresWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        return codec;
    }

}
}
