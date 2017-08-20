#include "LogarithmWrapperCodec.h"

namespace spotify
{
namespace json
{

using LogarithmWrapper = noise::module::Wrapper<noise::module::Logarithm>;

codec::object_t<LogarithmWrapper> default_codec_t<LogarithmWrapper>::codec()
{
    auto codec = codec::object<LogarithmWrapper>();
    codec.required("type", codec::eq<std::string>("Logarithm"));
    codec.required("SourceModule", codec::ignore_t<int>());
    codec.optional("Base",
                   [](const LogarithmWrapper& mw) {return mw.module->GetBase(); },
                   [](LogarithmWrapper& mw, double base) {mw.module->SetBase(base); });
    return codec;
}

}
}
