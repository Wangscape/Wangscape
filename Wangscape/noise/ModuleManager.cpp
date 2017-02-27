#include "ModuleManager.h"
#include <random>
#include <time.h>

#include <boost/filesystem.hpp>

#include "ModuleGroup.h"

namespace noise {

ModuleManager::ModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr)),
    mCentres("centre"),
    mHorizontalBorders("horizontal border"),
    mVerticalBorders("vertical border")
{
    boost::filesystem::path p(options.paths.directory);

    mCombiner = loadModuleGroup((p / options.combinerModuleGroup).string());

    for (auto it : options.centralModuleGroups)
    {
        mCentres.addSpecificModuleGroup(it.terrain, (p / it.filename).string());
    }
    for (auto it : options.horizontalBorderModuleGroups)
    {
        mHorizontalBorders.addSpecificModuleGroup(it.terrains, (p / it.filename).string());
    }
    for (auto it : options.verticalBorderModuleGroups)
    {
        mVerticalBorders.addSpecificModuleGroup(it.terrains, (p / it.filename).string());
    }
    boost::optional<std::string> default_module_filename;
    if (options.defaultModuleGroup)
    {
        default_module_filename = (p / options.defaultModuleGroup.get()).string();
    }
    for (const auto& terrain : options.terrains)
    {
        mCentres.tryAddDefaultModuleGroup(terrain.first, default_module_filename);
    }
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{t1, t2};
                mHorizontalBorders.tryAddDefaultModuleGroup(tp, default_module_filename);
                mVerticalBorders.tryAddDefaultModuleGroup(tp, default_module_filename);
            }
    }
    
}

ModuleGroup& ModuleManager::getVerticalBorder(TerrainID top, TerrainID bottom)
{
    return mVerticalBorders.at({top, bottom});
}

ModuleGroup& ModuleManager::getHorizontalBorder(TerrainID left, TerrainID right)
{
    return mHorizontalBorders.at({left, right});
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
