#pragma once

#include "NormLPQWrapperCodec.h"

namespace spotify
{
namespace json
{

using NormLPQWrapper = noise::module::Wrapper<noise::module::NormLPQ>;

codec::object_t<NormLPQWrapper> default_codec_t<NormLPQWrapper>::codec()
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

}
}
