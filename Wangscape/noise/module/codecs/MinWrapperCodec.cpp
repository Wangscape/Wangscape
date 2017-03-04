#include "MinWrapperCodec.h"

namespace spotify
{
namespace json
{

using MinWrapper = noise::module::Wrapper<noise::module::Min>;

codec::object_t<MinWrapper> default_codec_t<MinWrapper>::codec()
    {
        auto codec = codec::object<MinWrapper>();
        codec.required("type", codec::eq<std::string>("Min"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
