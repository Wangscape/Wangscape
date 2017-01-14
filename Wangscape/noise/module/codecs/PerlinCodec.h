#pragma once

#include <spotify/json.hpp>

#include <noise/noise.h>

#include "NoiseQualityCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::Perlin>
{
    using Perlin = noise::module::Perlin;
    static codec::object_t<Perlin> codec()
    {
        auto codec = codec::object<Perlin>();
        codec.required("type", codec::eq<std::string>("Perlin"));
        codec.optional("Frequency",
                       &Perlin::GetFrequency,
                       &Perlin::SetFrequency);
        codec.optional("Lacunarity",
                       &Perlin::GetLacunarity,
                       &Perlin::SetLacunarity);
        codec.optional("NoiseQuality",
                       &Perlin::GetNoiseQuality,
                       &Perlin::SetNoiseQuality);
        codec.optional("OctaveCount",
                       &Perlin::GetOctaveCount,
                       &Perlin::SetOctaveCount);
        codec.optional("Persistence",
                       &Perlin::GetPersistence,
                       &Perlin::SetPersistence);
        codec.optional("Seed",
                       &Perlin::GetSeed,
                       &Perlin::SetSeed);

        return codec;
    }
};

}
}
