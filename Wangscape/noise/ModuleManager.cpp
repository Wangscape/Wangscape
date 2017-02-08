#include "ModuleManager.h"
#include "module/ReseedableOps.h"
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
        p /= options.combinerModuleGroup;
        auto inserted = mHorizotalBorders.insert({it.terrains, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two horizontal border module groups with the same terrain pair");
        inserted.first->second.setSeeds(mRNG());
    }
    for (auto it : options.verticalBorderModuleGroups)
    {
        p /= options.combinerModuleGroup;
        auto inserted = mVerticalBorders.insert({it.terrains, loadModuleGroup(p.string())});
        p.remove_filename();

        if (!inserted.second)
            throw std::runtime_error("Tried to load two vertical border module groups with the same terrain pair");
        inserted.first->second.setSeeds(mRNG());
    }

    // TODO: Put a default module group field in options.
    // Use it for all module groups which aren't individually specified in options.
    for (const auto& terrain : options.terrains)
    {
        mStochasticMasks.insert({terrain.first, module::scaleBias(module::makePlaceholder(), 0.5, 0.5)});
    }
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{t1, t2};
                if (mBordersHorizontal.find(tp) == mBordersHorizontal.end())
                    mBordersHorizontal.insert({tp, module::makePlaceholder(mRNG())});
                if (mBordersVertical.find(tp) == mBordersVertical.end())
                    mBordersVertical.insert({tp, module::makePlaceholder(mRNG())});
            }
    }
}

module::ReseedablePtr ModuleManager::getBorderVertical(TerrainID top, TerrainID bottom, bool x_positive)
{
    ReseedablePtr& r = mBordersVertical.at({top, bottom});
    return module::selectQuadrant(r, x_positive, true);
}

module::ReseedablePtr ModuleManager::getBorderHorizontal(TerrainID left, TerrainID right, bool y_positive)
{
    ReseedablePtr& r = mBordersHorizontal.at({left, right});
    return module::selectQuadrant(r, true, y_positive);
}

module::ReseedablePtr& ModuleManager::getStochastic(TerrainID terrain)
{
    ReseedablePtr& r = mStochasticMasks.at(terrain);
    r->setSeed(mRNG());
    return r;
}

ModuleGroup ModuleManager::loadModuleGroup(std::string filename)
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
