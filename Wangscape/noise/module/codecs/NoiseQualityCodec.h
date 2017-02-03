#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::NoiseQuality>
{
    using NoiseQuality = noise::NoiseQuality;
    static codec::enumeration_t<NoiseQuality, codec::string_t> codec()
    {
        auto codec = codec::enumeration<NoiseQuality, std::string>({
            {NoiseQuality::QUALITY_FAST, "Fast"},
            {NoiseQuality::QUALITY_STD, "Standard"},
            {NoiseQuality::QUALITY_BEST, "Best"}
        });

        return codec;
    }
};

}
}
