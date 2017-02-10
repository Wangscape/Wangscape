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
    static codec::one_of_t<
        codec::enumeration_t<NoiseQuality, codec::number_t<int>>,
        codec::enumeration_t<NoiseQuality, codec::string_t>> codec()
    {
        auto codec_str = codec::enumeration<NoiseQuality, std::string>({
            {NoiseQuality::QUALITY_FAST, "Fast"},
            {NoiseQuality::QUALITY_STD, "Standard"},
            {NoiseQuality::QUALITY_BEST, "Best"}
        });
        auto codec_int = codec::enumeration<NoiseQuality, int>({
            {NoiseQuality::QUALITY_FAST, 0},
            {NoiseQuality::QUALITY_STD, 1},
            {NoiseQuality::QUALITY_BEST, 2}
        });
        return codec::one_of(codec_int, codec_str);
    }
};

}
}
