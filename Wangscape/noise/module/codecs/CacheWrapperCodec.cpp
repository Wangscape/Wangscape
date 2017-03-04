#include "CacheWrapperCodec.h"

namespace spotify
{
namespace json
{

using CacheWrapper = noise::module::Wrapper<noise::module::Cache>;

codec::object_t<CacheWrapper> default_codec_t<CacheWrapper>::codec()
    {
        auto codec = codec::object<CacheWrapper>();
        codec.required("type", codec::eq<std::string>("Cache"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
