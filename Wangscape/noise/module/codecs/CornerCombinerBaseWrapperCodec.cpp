#pragma once

#include "CornerCombinerBaseWrapperCodec.h"

namespace spotify
{
namespace json
{

using CornerCombinerBaseWrapper = noise::module::Wrapper<noise::module::CornerCombinerBase>;

codec::object_t<CornerCombinerBaseWrapper> default_codec_t<CornerCombinerBaseWrapper>::codec()
    {
        auto codec = codec::object<CornerCombinerBaseWrapper>();
        codec.required("type", codec::eq<std::string>("CornerCombinerBase"));
        codec.optional("Power",
                       [](const CornerCombinerBaseWrapper& mw) {return mw.module->GetPower(); },
                       [](CornerCombinerBaseWrapper& mw, double power) {mw.module->SetPower(power); });
        return codec;
    }

}
}
