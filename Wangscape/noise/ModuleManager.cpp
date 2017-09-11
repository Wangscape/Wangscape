#include "ModuleManager.h"
#include <random>
#include <time.h>

#include <boost/filesystem.hpp>

#include "ModuleGroup.h"

namespace noise {

ModuleManager::ModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr)),
    mCentres("centre"),
    mLeftBorders("horizontal border"),
    mTopBorders("vertical border")
{
    mBottomRightBorder = ModuleGroup::makeConstModuleGroup(0.0);

    boost::filesystem::path p(options.paths.directory);

    mCombiner = loadModuleGroup((p / options.combinerModuleGroup).string(), mRNG());

    for (auto it : options.centralModuleGroups)
    {
        mCentres.addSpecificModuleGroup(it.terrain, (p / it.filename).string(), mRNG());
    }
    for (auto it : options.leftBorderModuleGroups)
    {
        mLeftBorders.addSpecificModuleGroup(it.terrains, (p / it.filename).string(), mRNG());
    }
    for (auto it : options.topBorderModuleGroups)
    {
        mTopBorders.addSpecificModuleGroup(it.terrains, (p / it.filename).string(), mRNG());
    }
    boost::optional<std::string> default_module_filename;
    if (options.defaultModuleGroup)
    {
        default_module_filename = (p / options.defaultModuleGroup.get()).string();
    }
    for (const auto& terrain : options.terrains)
    {
        mCentres.tryAddDefaultModuleGroup(terrain.first, default_module_filename, mRNG());
    }
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{t1, t2};

                mLeftBorders.tryAddDefaultModuleGroup(tp, default_module_filename, mRNG());
                mTopBorders.tryAddDefaultModuleGroup(tp, default_module_filename, mRNG());
            }
    }
    
}

ModuleGroup& ModuleManager::getTopBorder(TerrainID top, TerrainID bottom)
{
    return mTopBorders.at({top, bottom});
}

ModuleGroup& ModuleManager::getLeftBorder(TerrainID left, TerrainID right)
{
    return mLeftBorders.at({left, right});
}

ModuleGroup & ModuleManager::getBottomRightBorder()
{
    return *mBottomRightBorder;
}

ModuleGroup& ModuleManager::getCentral(TerrainID terrain)
{
    ModuleGroup& r = mCentres.at(terrain);
    r.setSeeds(mRNG());
    return r;
}

ModuleGroup& ModuleManager::getCombiner()
{
    return *mCombiner;
}

} // namespace noise
