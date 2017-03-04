#include "ConstWrapperCodec.h"

namespace spotify
{
namespace json
{

using ConstWrapper = noise::module::Wrapper<noise::module::Const>;

codec::object_t<ConstWrapper> default_codec_t<ConstWrapper>::codec()
    {
        auto codec = codec::object<ConstWrapper>();
        codec.required("type", codec::eq<std::string>("Const"));
        codec.optional("ConstValue",
                       [](const ConstWrapper& mw) {return mw.module->GetConstValue(); },
                       [](ConstWrapper& mw, double const_value) {mw.module->SetConstValue(const_value); });
        return codec;
    }

}
}
