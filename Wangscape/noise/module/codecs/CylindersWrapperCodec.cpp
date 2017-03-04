#include "CylindersWrapperCodec.h"

namespace spotify
{
namespace json
{

using CylindersWrapper = noise::module::Wrapper<noise::module::Cylinders>;

codec::object_t<CylindersWrapper> default_codec_t<CylindersWrapper>::codec()
    {
        auto codec = codec::object<CylindersWrapper>();
        codec.required("type", codec::eq<std::string>("Cylinders"));
        codec.optional("Frequency",
                       [](const CylindersWrapper& mw) {return mw.module->GetFrequency(); },
                       [](CylindersWrapper& mw, double frequency) {mw.module->SetFrequency(frequency); });
        return codec;
    }

}
}
