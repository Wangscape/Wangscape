#include "ModuleManager.h"
#include "module/ModuleFactories.h"
#include <random>
#include <time.h>
#include <algorithm>

namespace noise {

ModuleManager::ModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr))
{
    for (const auto& terrain : options.terrains)
    {
        mStochasticMasks.insert({terrain.first, module::makePlaceholder().scaleBias(0.5, 0.5)});
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

Reseedable ModuleManager::getBorderVertical(TerrainID top, TerrainID bottom, bool x_positive)
{
    Reseedable& r = mBordersVertical.at({top, bottom});
    return module::makeQuadrantSelector(r, x_positive, true);
}

Reseedable ModuleManager::getBorderHorizontal(TerrainID left, TerrainID right, bool y_positive)
{
    Reseedable& r = mBordersHorizontal.at({left, right});
    return module::makeQuadrantSelector(r, true, y_positive);
}

Reseedable& ModuleManager::getStochastic(TerrainID terrain)
{
    Reseedable& r = mStochasticMasks.at(terrain);
    r.setSeed(mRNG());
    return r;
}

} // namespace noise
