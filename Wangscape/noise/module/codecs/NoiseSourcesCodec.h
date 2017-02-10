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
        auto module_list_as_single_codec = codec::transform(
            single_module_codec,
            [](const std::vector<std::string>& sources)
        {
            throw std::runtime_error("Cannot encode SourceModules as single string");
            return sources[0];
        },
            [](std::string source)
        {
            return std::vector<std::string>(1, source);
        });
        auto single_module_or_list_codec = codec::one_of(
            module_list_codec,
            module_list_as_single_codec);
        auto optional_single_module_codec = codec::optional(single_module_codec);
        auto optional_module_list_codec = codec::optional(module_list_codec);
        auto optional_single_module_or_list_codec = codec::optional(single_module_or_list_codec);
        codec.optional("SourceModule", &NoiseSources::sourceModules, optional_single_module_or_list_codec);
        codec.optional("ControlModule", &NoiseSources::controlModule, optional_single_module_codec);
        codec.optional("DisplaceModules", &NoiseSources::displaceModules, optional_module_list_codec);
        codec.optional(
            "XDisplaceModule",
            [](const NoiseSources&)
        {
            throw std::runtime_error("Cannot encode XDisplaceModule");
            return "";
        },
            [](NoiseSources& noise_sources, std::string module)
        { noise_sources.setXDisplaceModule(module); },
            codec::one_of(codec::omit<std::string>(), single_module_codec, codec::ignore<std::string>()));
        codec.optional(
            "YDisplaceModule",
            [](const NoiseSources&)
        {
            throw std::runtime_error("Cannot encode YDisplaceModule");
            return "";
        },
            [](NoiseSources& noise_sources, std::string module)
        { noise_sources.setYDisplaceModule(module); },
            codec::one_of(codec::omit<std::string>(), single_module_codec, codec::ignore<std::string>()));
        codec.optional(
            "ZDisplaceModule",
            [](const NoiseSources&)
        {
            throw std::runtime_error("Cannot encode ZDisplaceModule");
            return "";
        },
            [](NoiseSources& noise_sources, std::string module)
        { noise_sources.setZDisplaceModule(module); },
            codec::one_of(codec::omit<std::string>(), single_module_codec, codec::ignore<std::string>()));

        return codec;
    }
};

}
}
