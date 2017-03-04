#include "PowWrapperCodec.h"

namespace spotify
{
namespace json
{

using PowWrapper = noise::module::Wrapper<noise::module::Pow>;

codec::object_t<PowWrapper> default_codec_t<PowWrapper>::codec()
    {
        auto codec = codec::object<PowWrapper>();
        codec.required("type", codec::eq<std::string>("Pow"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Exponent",
                       [](const PowWrapper& mw) {return mw.module->GetExponent(); },
                       [](PowWrapper& mw, double exponent) {mw.module->SetExponent(exponent); });
        return codec;
    }

}
}
