#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Exp.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Exp>>
{
    using ExpWrapper = noise::module::Wrapper<noise::module::Exp>;
    static codec::object_t<ExpWrapper> codec()
    {
        auto codec = codec::object<ExpWrapper>();
        codec.required("type", codec::eq<std::string>("Exp"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Base",
                       [](const ExpWrapper& mw) {return mw.module.GetBase(); },
                       [](ExpWrapper& mw, double base) {mw.module.SetBase(base); });
        return codec;
    }
};
}
}
