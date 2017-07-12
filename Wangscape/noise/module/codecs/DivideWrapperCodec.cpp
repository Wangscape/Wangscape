#include "DivideWrapperCodec.h"

namespace spotify
{
namespace json
{

using DivideWrapper = noise::module::Wrapper<noise::module::Divide>;

codec::object_t<DivideWrapper> default_codec_t<DivideWrapper>::codec()
{
    auto codec = codec::object<DivideWrapper>();
    codec.required("type", codec::eq<std::string>("Divide"));
    codec.required("SourceModule", codec::ignore_t<int>());
    return codec;
}

}
}
