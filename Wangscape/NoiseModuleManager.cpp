#include "NoiseModuleManager.h"
#include "ModuleFactories.h"
#include <random>
#include <time.h>
#include <algorithm>

NoiseModuleManager::NoiseModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr))
{
    for (const auto& terrain : options.terrains)
    {
        mStochasticMasks.insert({terrain.first, makePlaceholder().scaleBias(0.5, 0.5)});
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

Reseedable NoiseModuleManager::getBorderVertical(TerrainID top, TerrainID bottom, bool x_positive)
{
    Reseedable& r = mBordersVertical.at({top, bottom});
    return makeQuadrantSelector(r, x_positive, true);
}

Reseedable NoiseModuleManager::getBorderHorizontal(TerrainID left, TerrainID right, bool y_positive)
{
    Reseedable& r = mBordersHorizontal.at({left, right});
    return makeQuadrantSelector(r, true, y_positive);
}

Reseedable& NoiseModuleManager::getStochastic(TerrainID terrain)
{
    Reseedable& r = mStochasticMasks.at(terrain);
    r.setSeed(mRNG());
    return r;
}
