#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/NormLPQ.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::NormLPQ>>
{
    using NormLPQWrapper = noise::module::Wrapper<noise::module::NormLPQ>;
    static codec::object_t<NormLPQWrapper> codec()
    {
        auto codec = codec::object<NormLPQWrapper>();
        codec.required("type", codec::eq<std::string>("NormLPQ"));
        codec.optional("P",
                       [](const NormLPQWrapper& mw) {return mw.module->GetP(); },
                       [](NormLPQWrapper& mw, double p) {mw.module->SetP(p); });
        codec.optional("Q",
                       [](const NormLPQWrapper& mw) {return mw.module->GetQ(); },
                       [](NormLPQWrapper& mw, double q) {mw.module->SetQ(q); });
        return codec;
    }
};
}
}
