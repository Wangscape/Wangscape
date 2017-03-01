#pragma once

#include "BillowWrapperCodec.h"

namespace spotify
{
namespace json
{

using BillowWrapper = noise::module::Wrapper<noise::module::Billow>;

codec::object_t<BillowWrapper> default_codec_t<BillowWrapper>::codec()
    {
        auto codec = codec::object<BillowWrapper>();
        codec.required("type", codec::eq<std::string>("Billow"));
        codec.optional("Frequency",
                       [](const BillowWrapper& mw) {return mw.module->GetFrequency(); },
                       [](BillowWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        codec.optional("Lacunarity",
                       [](const BillowWrapper& mw) {return mw.module->GetLacunarity(); },
                       [](BillowWrapper& mw, double lacunarity) {mw.module->SetLacunarity(lacunarity); });
        codec.optional("Persistence",
                       [](const BillowWrapper& mw) {return mw.module->GetPersistence(); },
                       [](BillowWrapper& mw, double persistence) {mw.module->SetPersistence(persistence); });
        codec.optional("OctaveCount",
                       [](const BillowWrapper& mw) {return mw.module->GetOctaveCount(); },
                       [](BillowWrapper& mw, int octave_count) {mw.module->SetOctaveCount(octave_count); });
        codec.optional("NoiseQuality",
                       [](const BillowWrapper& mw) {return mw.module->GetNoiseQuality(); },
                       [](BillowWrapper& mw, noise::NoiseQuality noise_quality) {mw.module->SetNoiseQuality(noise_quality); });
        codec.optional("Seed",
                       [](const BillowWrapper& mw) {return mw.module->GetSeed(); },
                       [](BillowWrapper& mw, int seed) {mw.module->SetSeed(seed); });
        return codec;
    }

}
}
