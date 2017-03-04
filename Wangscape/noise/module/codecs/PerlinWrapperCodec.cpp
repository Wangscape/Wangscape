#include "PerlinWrapperCodec.h"

namespace spotify
{
namespace json
{

using PerlinWrapper = noise::module::Wrapper<noise::module::Perlin>;

codec::object_t<PerlinWrapper> default_codec_t<PerlinWrapper>::codec()
    {
        auto codec = codec::object<PerlinWrapper>();
        codec.required("type", codec::eq<std::string>("Perlin"));
        codec.optional("Seed",
                       [](const PerlinWrapper& mw) {return mw.module->GetSeed(); },
                       [](PerlinWrapper& mw, int seed) {mw.module->SetSeed(seed); });
        codec.optional("Frequency",
                       [](const PerlinWrapper& mw) {return mw.module->GetFrequency(); },
                       [](PerlinWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        codec.optional("Persistence",
                       [](const PerlinWrapper& mw) {return mw.module->GetPersistence(); },
                       [](PerlinWrapper& mw, double persistence) {mw.module->SetPersistence(persistence); });
        codec.optional("Lacunarity",
                       [](const PerlinWrapper& mw) {return mw.module->GetLacunarity(); },
                       [](PerlinWrapper& mw, double lacunarity) {mw.module->SetLacunarity(lacunarity); });
        codec.optional("OctaveCount",
                       [](const PerlinWrapper& mw) {return mw.module->GetOctaveCount(); },
                       [](PerlinWrapper& mw, int octave_count) {mw.module->SetOctaveCount(octave_count); });
        codec.optional("NoiseQuality",
                       [](const PerlinWrapper& mw) {return mw.module->GetNoiseQuality(); },
                       [](PerlinWrapper& mw, noise::NoiseQuality noise_quality) {mw.module->SetNoiseQuality(noise_quality); });
        return codec;
    }

}
}
