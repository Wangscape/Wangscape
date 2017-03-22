#include "ForwardWrapperCodec.h"

namespace spotify
{
namespace json
{

using ForwardWrapper = noise::module::Wrapper<noise::module::Forward>;

codec::object_t<ForwardWrapper> default_codec_t<ForwardWrapper>::codec()
    {
        auto codec = codec::object<ForwardWrapper>();
        codec.required("type", codec::eq<std::string>("Forward"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
