#include "DisplaceWrapperCodec.h"

namespace spotify
{
namespace json
{

using DisplaceWrapper = noise::module::Wrapper<noise::module::Displace>;

codec::object_t<DisplaceWrapper> default_codec_t<DisplaceWrapper>::codec()
    {
        auto codec = codec::object<DisplaceWrapper>();
        codec.required("type", codec::eq<std::string>("Displace"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
