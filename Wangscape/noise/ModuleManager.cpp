#include "ModuleManager.h"
#include <random>
#include <time.h>
#include <algorithm>

#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>

#include "EncodedModuleGroup.h"
#include "codecs/EncodedModuleGroupCodec.h"

namespace noise {

ModuleManager::ModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr))
{
    boost::filesystem::path p(options.directory);

    p /= options.combinerModuleGroup;
    mCombiner = loadModuleGroup(p.string());
    p.remove_filename();

    for (auto it : options.centralModuleGroups)
    {
        p /= it.filename;
        auto inserted = mCentres.insert({it.terrain, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two central module groups with the same terrain");
    }
    for (auto it : options.horizontalBorderModuleGroups)
    {
        p /= it.filename;
        auto inserted = mHorizontalBorders.insert({it.terrains, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two horizontal border module groups with the same terrain pair");
        inserted.first->second->setSeeds(mRNG());
    }
    for (auto it : options.verticalBorderModuleGroups)
    {
        p /= it.filename;
        auto inserted = mVerticalBorders.insert({it.terrains, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two vertical border module groups with the same terrain pair");
        inserted.first->second->setSeeds(mRNG());
    }
    if (options.defaultModuleGroup)
    {
        p /= options.defaultModuleGroup.get();
    }
    for (const auto& terrain : options.terrains)
    {
        if (mCentres.find(terrain.first) == mCentres.cend())
        {
            if (options.defaultModuleGroup)
                mCentres.insert({terrain.first, loadModuleGroup(p.string())});
            else
                throw std::runtime_error("Missing central module group, and no default module group");
        }
    }
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{t1, t2};
                if (mHorizontalBorders.find(tp) == mHorizontalBorders.end())
                {
                    if (options.defaultModuleGroup)
                        mHorizontalBorders.insert({tp, loadModuleGroup(p.string())});
                    else
                        throw std::runtime_error("Missing vertical module group, and no default module group");
                }
                if (mVerticalBorders.find(tp) == mVerticalBorders.end())
                {
                    if(options.defaultModuleGroup)
                        mVerticalBorders.insert({tp, loadModuleGroup(p.string())});
                    else
                        throw std::runtime_error("Missing vertical module group, and no default module group");
                }
            }
    }
    
}

ModuleGroup& ModuleManager::getVerticalBorder(TerrainID top, TerrainID bottom)
{
    return *mVerticalBorders.at({top, bottom});
}

ModuleGroup& ModuleManager::getHorizontalBorder(TerrainID left, TerrainID right)
{
    return *mHorizontalBorders.at({left, right});
}

ModuleGroup& ModuleManager::getCentral(TerrainID terrain)
{
    ModuleGroup& r = *mCentres.at(terrain);
    r.setSeeds(mRNG());
    return r;
}

ModuleGroup& ModuleManager::getCombiner()
{
    return *mCombiner;
}

std::shared_ptr<ModuleGroup> loadModuleGroup(std::string filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not open options file");
    }

    std::string str{std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()};
    EncodedModuleGroup encoded_module_group;
    try
    {
        encoded_module_group = spotify::json::decode<EncodedModuleGroup>(str.c_str());
    }
    catch (const spotify::json::decode_exception& e)
    {
        std::cout << "spotify::json::decode_exception encountered at "
            << e.offset()
            << ": "
            << e.what();
        throw;
    }
    encoded_module_group.decode();
    return encoded_module_group.moduleGroup;
}

} // namespace noise
