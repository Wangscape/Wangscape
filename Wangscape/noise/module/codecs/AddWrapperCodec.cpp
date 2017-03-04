#include "AddWrapperCodec.h"

namespace spotify
{
namespace json
{

using AddWrapper = noise::module::Wrapper<noise::module::Add>;

codec::object_t<AddWrapper> default_codec_t<AddWrapper>::codec()
    {
        auto codec = codec::object<AddWrapper>();
        codec.required("type", codec::eq<std::string>("Add"));
        codec.required("SourceModule", codec::ignore_t<int>());
        return codec;
    }

}
}
