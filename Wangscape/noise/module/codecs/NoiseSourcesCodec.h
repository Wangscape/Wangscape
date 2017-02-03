#pragma once


#include <spotify/json.hpp>
#include <spotify/json/codec/boost.hpp>

#include "noise/module/NoiseSources.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<noise::module::NoiseSources>
{
    typedef noise::module::NoiseSources NoiseSources;
    static codec::object_t<NoiseSources> codec()
    {
        auto codec = codec::object<NoiseSources>();
        auto single_module_codec = codec::string();
        auto module_list_codec = codec::array<std::vector<std::string>>(single_module_codec);
        auto optional_single_module_codec = codec::optional(single_module_codec);
        auto optional_module_list_codec = codec::optional(module_list_codec);
        codec.optional("SourceModule", &NoiseSources::sourceModules, optional_module_list_codec);
        codec.optional("ControlModule", &NoiseSources::controlModule, optional_single_module_codec);
        codec.optional("DisplaceModule", &NoiseSources::displaceModules, optional_module_list_codec);
        return codec;
    }
};

}
}
