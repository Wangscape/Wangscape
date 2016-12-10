#include "MetaOutput.h"
#include <ostream>
#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>



MetaOutput::MetaOutput()
{
    mTileData.SetArray();
    mTilesetData.SetObject();
}


MetaOutput::~MetaOutput()
{
}

void MetaOutput::addTile(std::vector<Options::TerrainID> corners, std::string filename, size_t offset_x, size_t offset_y)
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
    v_item.AddMember("corners",v_corners, allocator);
    rapidjson::Value v(filename.c_str(), allocator);
    v_item.AddMember("file", v, allocator);
    v_item.AddMember("x", offset_x, allocator);
    v_item.AddMember("y", offset_y, allocator);
    mTileData.PushBack(v_item, allocator);
}

void MetaOutput::addTileset(std::vector<Options::TerrainID> terrains, std::string filename, size_t size_x, size_t size_y)
{
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

void MetaOutput::writeTileData(std::string filename)
{
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mTileData.Accept(writer);
}

void MetaOutput::writeTilesetData(std::string filename)
{
    std::ofstream ofs(filename);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mTilesetData.Accept(writer);
}

const rapidjson::Document & MetaOutput::getTileData() const
{
    return mTileData;
}

const rapidjson::Document & MetaOutput::getTilesetData() const
{
    return mTilesetData;
}
