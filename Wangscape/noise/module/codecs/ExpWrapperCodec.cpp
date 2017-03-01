#include "ExpWrapperCodec.h"

namespace spotify
{
namespace json
{

using ExpWrapper = noise::module::Wrapper<noise::module::Exp>;

codec::object_t<ExpWrapper> default_codec_t<ExpWrapper>::codec()
    {
        auto codec = codec::object<ExpWrapper>();
        codec.required("type", codec::eq<std::string>("Exp"));
        codec.required("SourceModule", codec::ignore_t<int>());
        codec.optional("Base",
                       [](const ExpWrapper& mw) {return mw.module->GetBase(); },
                       [](ExpWrapper& mw, double base) {mw.module->SetBase(base); });
        return codec;
    }

}
}
