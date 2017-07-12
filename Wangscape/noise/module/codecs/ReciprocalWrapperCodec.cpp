#include "ReciprocalWrapperCodec.h"

namespace spotify
{
namespace json
{

using ReciprocalWrapper = noise::module::Wrapper<noise::module::Reciprocal>;

codec::object_t<ReciprocalWrapper> default_codec_t<ReciprocalWrapper>::codec()
{
    auto codec = codec::object<ReciprocalWrapper>();
    codec.required("type", codec::eq<std::string>("Reciprocal"));
    codec.required("SourceModule", codec::ignore_t<int>());
    return codec;
}

}
}
