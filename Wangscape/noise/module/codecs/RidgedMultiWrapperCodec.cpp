#include "RidgedMultiWrapperCodec.h"

namespace spotify
{
namespace json
{

using RidgedMultiWrapper = noise::module::Wrapper<noise::module::RidgedMulti>;

codec::object_t<RidgedMultiWrapper> default_codec_t<RidgedMultiWrapper>::codec()
    {
        auto codec = codec::object<RidgedMultiWrapper>();
        codec.required("type", codec::eq<std::string>("RidgedMulti"));
        codec.optional("Frequency",
                       [](const RidgedMultiWrapper& mw) {return mw.module->GetFrequency(); },
                       [](RidgedMultiWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        codec.optional("Lacunarity",
                       [](const RidgedMultiWrapper& mw) {return mw.module->GetLacunarity(); },
                       [](RidgedMultiWrapper& mw, double lacunarity) {mw.module->SetLacunarity(lacunarity); });
        codec.optional("OctaveCount",
                       [](const RidgedMultiWrapper& mw) {return mw.module->GetOctaveCount(); },
                       [](RidgedMultiWrapper& mw, int octave_count) {mw.module->SetOctaveCount(octave_count); });
        codec.optional("NoiseQuality",
                       [](const RidgedMultiWrapper& mw) {return mw.module->GetNoiseQuality(); },
                       [](RidgedMultiWrapper& mw, noise::NoiseQuality noise_quality) {mw.module->SetNoiseQuality(noise_quality); });
        codec.optional("Seed",
                       [](const RidgedMultiWrapper& mw) {return mw.module->GetSeed(); },
                       [](RidgedMultiWrapper& mw, int seed) {mw.module->SetSeed(seed); });
        return codec;
    }

}
}
