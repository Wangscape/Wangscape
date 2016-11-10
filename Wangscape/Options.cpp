#include "Options.h"
#include <iostream>

Options::Options(const rapidjson::Document& d)
{
    auto& o = d.GetObject();
    {
        auto& doc_tile_format = o.FindMember("TileFormat")->value.GetObject();

        resolution = doc_tile_format.FindMember("Resolution")->value.GetInt();

        auto it = doc_tile_format.FindMember("Colours");
        if (it != doc_tile_format.end())
            colours = it->value.GetString();
        // Be kind
        it = doc_tile_format.FindMember("Colors");
        if (it != doc_tile_format.end())
            std::cout << "Found #/TileFormat/Colors in options, did you mean ""Colours""?";

        it = doc_tile_format.FindMember("BitDepth");
        if (it != doc_tile_format.end())
            bitDepth = it->value.GetInt();

        it = doc_tile_format.FindMember("FileType");
        if (it != doc_tile_format.end())
            fileType = it->value.GetString();
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
                TerrainNamePair(
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
