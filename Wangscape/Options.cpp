#include "Options.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <stdexcept>
Options::Options(std::string filename):
    filename(filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not read options file");
    }
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document options_document;
    options_document.ParseStream(isw);
    if (options_document.HasParseError())
    {
        throw std::runtime_error("Could not parse options file");
        //std::cout << "Options document has parse error at offset " << (unsigned)options_document.GetErrorOffset() << ":\n";
        //std::cout << GetParseError_En(options_document.GetParseError()) << "\n";
    }
    // At present *no* validation is performed!
    //OptionsValidator ov(&options_document);
    //if (ov.hasError())
    //{
    //    std::cout << "Could not generate tileset.\n";
    //    std::cout << ov.getError().c_str();
    //}
    initialise(options_document);
}

void Options::initialise(const rapidjson::Document& d)
{
    auto& o = d.GetObject();
    {
        auto& doc_tile_format = o.FindMember("TileFormat")->value.GetObject();

        resolution = doc_tile_format.FindMember("Resolution")->value.GetInt();

        auto it = doc_tile_format.FindMember("FileType");
        if (it != doc_tile_format.end())
            fileType = it->value.GetString();
    }
    {
        auto& doc_metaoutput = o.FindMember("MetaOutput")->value.GetObject();

        tileDataFilename = doc_metaoutput.FindMember("TileData")->value.GetString();

        tilesetDataFilename = doc_metaoutput.FindMember("TilesetData")->value.GetString();
    }
    outputDirectory = o.FindMember("OutputDirectory")->value.GetString();
    {
        auto& doc_terrains = o.FindMember("Terrains")->value.GetObject();
        for (const auto& it : doc_terrains)
        {
            const auto& v = it.value.GetObject();
            terrains.insert(std::make_pair(
                it.name.GetString(),
                TerrainSpec(
                    v.FindMember("FullName")->value.GetString(),
                    v.FindMember("ShortName")->value.GetString(),
                    v.FindMember("FileName")->value.GetString(),
                    v.FindMember("OffsetX")->value.GetInt(),
                    v.FindMember("OffsetY")->value.GetInt())
            ));
        }
    }
    {
        auto& doc_cliques = o.FindMember("Cliques")->value.GetArray();
        for (const auto& it : doc_cliques)
        {
            const auto& doc_c = it.GetArray();
            Clique c;
            for (const auto& jt : doc_c)
            {
                c.push_back(jt.GetString());
            }
            cliques.push_back(c);
        }
    }
    {
        auto& doc_border_offsets = o.FindMember("BorderOffsets")->value.GetArray();
        for (const auto& it : doc_border_offsets)
        {
            const auto& doc_bos = it.GetObject();
            const auto& doc_terrain_pair = doc_bos.FindMember("Terrains")->value.GetArray();
            borderOffsets.insert(std::make_pair(
                TerrainIDPair(
                    doc_terrain_pair.Begin()->GetString(),
                    (doc_terrain_pair.Begin()+1)->GetString()),
                BorderOffsetSpec(
                    doc_bos.FindMember("Horizontal")->value.GetInt(),
                    doc_bos.FindMember("Vertical")->value.GetInt())
            ));
        }
    }
}

Options::~Options()
{
}
