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
    mBottomRightBorder = ModuleGroup::makeConstModuleGroup(0.0);

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
    for (auto it : options.leftBorderModuleGroups)
    {
        p /= it.filename;
        auto inserted = mLeftBorders.insert({it.terrains, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two horizontal border module groups with the same terrain pair");
        inserted.first->second->setSeeds(mRNG());
    }
    for (auto it : options.topBorderModuleGroups)
    {
        p /= it.filename;
        auto inserted = mTopBorders.insert({it.terrains, loadModuleGroup(p.string())});
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
                if (mLeftBorders.find(tp) == mLeftBorders.end())
                {
                    if (options.defaultModuleGroup)
                        mLeftBorders.insert({tp, loadModuleGroup(p.string())});
                    else
                        throw std::runtime_error("Missing left border module group, and no default module group");
                }
                if (mTopBorders.find(tp) == mTopBorders.end())
                {
                    if(options.defaultModuleGroup)
                        mTopBorders.insert({tp, loadModuleGroup(p.string())});
                    else
                        throw std::runtime_error("Missing top border module group, and no default module group");
                }
            }
    }
    
}

ModuleGroup& ModuleManager::getTopBorder(TerrainID top, TerrainID bottom)
{
    return *mTopBorders.at({top, bottom});
}

ModuleGroup& ModuleManager::getLeftBorder(TerrainID left, TerrainID right)
{
    return *mLeftBorders.at({left, right});
}

ModuleGroup & ModuleManager::getBottomRightBorder()
{
    return *mBottomRightBorder;
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
