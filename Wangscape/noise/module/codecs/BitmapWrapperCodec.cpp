#include "BitmapWrapperCodec.h"
#include "codecs/RectCodec.h"

namespace spotify
{
namespace json
{

using BitmapWrapper = noise::module::Wrapper<noise::module::Bitmap>;

codec::object_t<BitmapWrapper> default_codec_t<BitmapWrapper>::codec()
    {
        auto codec = codec::object<BitmapWrapper>();
        codec.required("type", codec::eq<std::string>("Bitmap"));
        codec.optional("MaxScale",
                       [](const BitmapWrapper& mw) {return mw.module->GetMaxScale(); },
                       [](BitmapWrapper& mw, bool max_scale) {mw.module->SetMaxScale(max_scale); });
        codec.optional("Filename",
                       [](const BitmapWrapper& mw) {return mw.module->GetFilename(); },
                       [](BitmapWrapper& mw, std::string filename) {mw.module->SetFilename(filename); });
        codec.optional("DefaultValue",
                       [](const BitmapWrapper& mw) {return mw.module->GetDefaultValue(); },
                       [](BitmapWrapper& mw, double default_value) {mw.module->SetDefaultValue(default_value); });
        codec.optional("Region",
                       [](const BitmapWrapper& mw) {return mw.module->GetRegion(); },
                       [](BitmapWrapper& mw, sf::Rect<double> region) {mw.module->SetRegion(region); });
        return codec;
    }

}
}
