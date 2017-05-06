#pragma once

#include <spotify/json.hpp>
#include <spotify/json/codec/boost.hpp>

#include "Options.h"
#include "metaoutput/codecs/FilenamesCodec.h"
#include "TerrainSpecCodec.h"
#include "TileFormatCodec.h"
#include "spotify/json/codec/boost.hpp"
#include "BorderModuleGroupLocationCodec.h"
#include "TerrainModuleGroupLocationCodec.h"

namespace spotify
{
namespace json
{

template<>
struct default_codec_t<Options>
{
    static codec::object_t<Options> codec()
    {
        auto codec = codec::object<Options>();
        codec.required("OutputDirectory", &Options::outputDirectory);
        codec.required("Terrains", &Options::terrains);
        codec.required("TileFormat", &Options::tileFormat);
        codec.required("Cliques", &Options::cliques);
        codec.required("MetaOutput", &Options::outputFilenames);
        codec.required("AlphaCalculatorMode", &Options::calculatorMode,
                       codec::enumeration<tilegen::alpha::CalculatorMode, std::string>({
                           {tilegen::alpha::CalculatorMode::Max, "Max"},
                           {tilegen::alpha::CalculatorMode::Linear, "Linear"},
                           {tilegen::alpha::CalculatorMode::TopTwo, "TopTwo"},
                           {tilegen::alpha::CalculatorMode::Dither, "Dither"}}));
        codec.optional("AlphaCalculatorTopTwoPower", &Options::alphaCalculatorTopTwoPower);
        codec.required("CombinerModuleGroup", &Options::combinerModuleGroup);
        codec.optional("DefaultModuleGroup", &Options::defaultModuleGroup);
        codec.optional("CentralModuleGroups", &Options::centralModuleGroups);
        codec.optional("LeftBorderModuleGroups", &Options::leftBorderModuleGroups);
        codec.optional("TopBorderModuleGroups", &Options::topBorderModuleGroups);
        codec.required("DebugOutput", &Options::debugOutput);
        codec.optional("DebugTileResolution", &Options::debugTileResolution);
        return codec;
    }
};

}
}
