#include "NoiseModuleManager.h"
#include "ModuleFactories.h"
#include <random>
#include <time.h>

NoiseModuleManager::NoiseModuleManager(const Options & options) :
    mRNG(time(nullptr))
{
    for (const auto& terrain : options.terrains)
    {
        mStochasticMasks.insert({terrain.first, makePlaceholder()});
    }
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{t1, t2};
                if (mBordersHorizontal.find(tp) == mBordersHorizontal.end())
                    mBordersHorizontal.insert({tp, makePlaceholder(mRNG())});
                if (mBordersVertical.find(tp) == mBordersVertical.end())
                    mBordersVertical.insert({tp, makePlaceholder(mRNG())});
            }
    }
}

NoiseModuleManager::~NoiseModuleManager()
{
}

Reseedable& NoiseModuleManager::getBorderVertical(TerrainID top, TerrainID bottom)
{
    return mBordersVertical.at({top, bottom});
}

Reseedable& NoiseModuleManager::getBorderHorizontal(TerrainID left, TerrainID right)
{
    return mBordersHorizontal.at({left, right});
}

Reseedable& NoiseModuleManager::getStochastic(TerrainID terrain)
{
    Reseedable& r = mStochasticMasks.at(terrain);
    r.setSeed(mRNG());
    return r;
}
