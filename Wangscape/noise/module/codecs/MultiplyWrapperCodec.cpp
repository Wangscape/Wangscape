#include "MultiplyWrapperCodec.h"

namespace spotify
{
namespace json
{

using MultiplyWrapper = noise::module::Wrapper<noise::module::Multiply>;

codec::object_t<MultiplyWrapper> default_codec_t<MultiplyWrapper>::codec()
    {
        auto codec = codec::object<MultiplyWrapper>();
        codec.required("type", codec::eq<std::string>("Multiply"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
