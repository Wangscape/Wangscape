#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>
#include "noise/module/Wrapper.h"
#include "noise/module/Bitmap.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Wrapper<noise::module::Bitmap>>
{
    using BitmapWrapper = noise::module::Wrapper<noise::module::Bitmap>;
    static codec::object_t<BitmapWrapper> codec();
};
}
}
