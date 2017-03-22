#include "MaxWrapperCodec.h"

namespace spotify
{
namespace json
{

using MaxWrapper = noise::module::Wrapper<noise::module::Max>;

codec::object_t<MaxWrapper> default_codec_t<MaxWrapper>::codec()
    {
        auto codec = codec::object<MaxWrapper>();
        codec.required("type", codec::eq<std::string>("Max"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
