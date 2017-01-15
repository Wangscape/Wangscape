#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>

#include "NoiseQualityCodec.h"
#include "noise/module/Reseedable.h"

namespace spotify
{
namespace json
{

template<typename M>
struct default_codec_t<noise::module::Reseedable<M>>
{
    using Reseedable = noise::module::Reseedable;
    static codec::object_t<Reseedable<M>> codec()
    {
        auto codec = codec::object<Reseedable<M>>();

        return codec;
    }
};

}
}
