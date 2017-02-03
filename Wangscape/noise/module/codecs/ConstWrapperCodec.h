#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Const>>
{
    using ConstWrapper = noise::module::Wrapper<noise::module::Const>;
    static codec::object_t<ConstWrapper> codec()
    {
        auto codec = codec::object<ConstWrapper>();
        codec.required("type", codec::eq<std::string>("Const"));
        codec.optional("ConstValue",
                       [](const ConstWrapper& mw) {return mw.module.GetConstValue(); },
                       [](ConstWrapper& mw, double const_value) {mw.module.SetConstValue(const_value); });
        return codec;
    }
};
}
}
