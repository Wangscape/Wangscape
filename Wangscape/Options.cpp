#include "Options.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <stdexcept>
#include <boost/filesystem.hpp>
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
    const auto& o = d.GetObject();
    {
        const auto& doc_tile_format = o.FindMember("TileFormat")->value.GetObject();

        resolution = doc_tile_format.FindMember("Resolution")->value.GetInt();

        auto it = doc_tile_format.FindMember("FileType");
        if (it != doc_tile_format.end())
            fileType = it->value.GetString();
    }
    {
        const auto& doc_metaoutput = o.FindMember("MetaOutput")->value.GetObject();

        tileDataFilename = doc_metaoutput.FindMember("TileData")->value.GetString();
        tileGroupsFilename = doc_metaoutput.FindMember("TileGroups")->value.GetString();
        tilesetDataFilename = doc_metaoutput.FindMember("TilesetData")->value.GetString();
        terrainHypergraphFilename = doc_metaoutput.FindMember("TerrainHypergraph")->value.GetString();
    }
    outputDirectory = o.FindMember("OutputDirectory")->value.GetString();
    boost::filesystem::path p(filename);
    p.remove_filename();
    p.append(outputDirectory);
    boost::filesystem::create_directories(p);
    relativeOutputDirectory = p.string();
    {
        const auto& doc_terrains = o.FindMember("Terrains")->value.GetObject();
        for (const auto& it : doc_terrains)
        {
            const auto& v = it.value.GetObject();
            terrains.insert(std::make_pair(
                it.name.GetString(),
                TerrainSpec(
                    v.FindMember("FullName")->value.GetString(),
                    v.FindMember("FileName")->value.GetString(),
                    v.FindMember("OffsetX")->value.GetInt(),
                    v.FindMember("OffsetY")->value.GetInt())
            ));
        }
    }
    {
        const auto& doc_cliques = o.FindMember("Cliques")->value.GetArray();
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
}

Options::~Options()
{
}
