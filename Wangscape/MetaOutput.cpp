#include "MetaOutput.h"
#include <ostream>
#include <sstream>
#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <boost/filesystem.hpp>



MetaOutput::MetaOutput()
{
    mTileData.SetArray();
    mTilesetData.SetObject();
    mTileGroups.SetObject();
}


MetaOutput::~MetaOutput()
{
}

void MetaOutput::addTile(std::vector<Options::TerrainID> corners, std::string filename, size_t offset_x, size_t offset_y)
{
    {
        rapidjson::Document::AllocatorType& allocator = mTileData.GetAllocator();
        rapidjson::Value v_corners;
        v_corners.SetArray();
        for (auto corner : corners)
        {
            rapidjson::Value v(corner.c_str(), allocator);
            v_corners.PushBack(v, allocator);
        }
        rapidjson::Value v_item;
        v_item.SetObject();
        v_item.AddMember("corners", v_corners, allocator);
        rapidjson::Value v(filename.c_str(), allocator);
        v_item.AddMember("file", v, allocator);
        v_item.AddMember("x", offset_x, allocator);
        v_item.AddMember("y", offset_y, allocator);
        mTileData.PushBack(v_item, allocator);
    }
    {
        rapidjson::Document::AllocatorType& allocator = mTileGroups.GetAllocator();
        rapidjson::Value v_item;
        v_item.SetObject();
        {
            rapidjson::Value v(filename.c_str(), allocator);
            v_item.AddMember("file", v, allocator);
        }
        v_item.AddMember("x", offset_x, allocator);
        v_item.AddMember("y", offset_y, allocator);

        std::stringstream ss;
        for (size_t i = 0; i < corners.size() - 1; i++)
            ss << corners[i] << ".";
        ss << *corners.rbegin();
        std::string tile_spec = ss.str();

        auto it = mTileGroups.FindMember(tile_spec.c_str());
        if (it == mTileGroups.MemberEnd())
        {
            rapidjson::Value v_options;
            v_options.SetArray();
            v_options.PushBack(v_item, allocator);
            {
                rapidjson::Value v(tile_spec.c_str(), allocator);
                mTileGroups.AddMember(v, v_options, allocator);
            }
        }
        else
            (*it).value.PushBack(v_item, allocator);
    }
}

void MetaOutput::addTileset(std::vector<Options::TerrainID> terrains, std::string filename, size_t size_x, size_t size_y)
{
    TerrainSet clique;
    for (auto t : terrains)
    {
        clique.insert(t);
    }
    for (auto t : terrains)
    {
        auto it = mTerrainHypergraph.insert({ t, TerrainSetSet() });
        (*it.first).second.insert(clique);
    }

    rapidjson::Document::AllocatorType& allocator = mTilesetData.GetAllocator();

    rapidjson::Value v_terrains;
    v_terrains.SetArray();
    for (auto terrain : terrains)
    {
        rapidjson::Value v(terrain.c_str(), allocator);
        v_terrains.PushBack(v, allocator);
    }
    rapidjson::Value v_item;
    v_item.SetObject();
    v_item.AddMember("terrains", v_terrains, allocator);
    rapidjson::Value v(filename.c_str(), allocator);
    v_item.AddMember("x", size_x, allocator);
    v_item.AddMember("y", size_y, allocator);
    mTilesetData.AddMember(v, v_item, allocator);
}

void MetaOutput::setResolution(size_t resolution)
{
    rapidjson::Document::AllocatorType& allocator = mTilesetData.GetAllocator();
    auto it = mTilesetData.FindMember("resolution");
    if (it == mTilesetData.MemberEnd())
        mTilesetData.AddMember("resolution", resolution, allocator);
    else
        (*it).value.Set(resolution);
}

void MetaOutput::writeTileData(std::string filename) const
{
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mTileData.Accept(writer);
}

void MetaOutput::writeTileGroups(std::string filename) const
{
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mTileGroups.Accept(writer);
}

void MetaOutput::writeTilesetData(std::string filename) const
{
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mTilesetData.Accept(writer);
}

void MetaOutput::writeTerrainHypergraph(std::string filename) const
{
    rapidjson::Document tad;
    auto& allocator = tad.GetAllocator();
    tad.SetObject();
    for (const auto& it : mTerrainHypergraph)
    {
        rapidjson::Value v_item;
        v_item.SetArray();
        for (const auto& clique : it.second)
        {
            rapidjson::Value v_clique;
            v_clique.SetArray();
            for (const auto& t : clique)
            {
                rapidjson::Value v(t.c_str(), allocator);
                v_clique.PushBack(v, allocator);
            }
            v_item.PushBack(v_clique, allocator);
        }
        rapidjson::Value v(it.first.c_str(), allocator);
        tad.AddMember(v, v_item, allocator);
    }

    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    tad.Accept(writer);

}

void MetaOutput::writeAll(const Options & options) const
{
    boost::filesystem::path p(options.relativeOutputDirectory);

    p.append(options.tilesetDataFilename);
    writeTilesetData(p.string());
    p.remove_filename();

    p.append(options.tileDataFilename);
    writeTileData(p.string());
    p.remove_filename();

    p.append(options.tileGroupsFilename);
    writeTileGroups(p.string());
    p.remove_filename();

    p.append(options.terrainHypergraphFilename);
    writeTerrainHypergraph(p.string());
}

const rapidjson::Document & MetaOutput::getTileData() const
{
    return mTileData;
}

const rapidjson::Document & MetaOutput::getTileGroups() const
{
    return mTileGroups;
}

const rapidjson::Document & MetaOutput::getTilesetData() const
{
    return mTilesetData;
}

const MetaOutput::TerrainHypergraph & MetaOutput::getTerrainHypergraph() const
{
    return mTerrainHypergraph;
}
