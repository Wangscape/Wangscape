#include "ModuleManager.h"
#include "module/ReseedableOps.h"
#include <random>
#include <time.h>
#include <algorithm>

namespace noise {

ModuleManager::ModuleManager(const Options & options) :
    mRNG((unsigned int)time(nullptr))
{
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

} // namespace noise
