#include "NoiseModuleManager.h"
#include "ModuleFactories.h"
#include <random>
#include <time.h>

NoiseModuleManager::NoiseModuleManager(const Options & options)
{
    for (const auto& terrain : options.terrains)
    {
        mStochasticMasks.insert({ terrain.first, makePlaceholder() });
    }
    std::mt19937 rng;
    rng.seed(time(nullptr));
    for (const auto& clique : options.cliques)
    {
        // At least n*(n-1)/2 duplicates will be checked in each clique.
        for (const auto& t1 : clique)
            for (const auto& t2 : clique)
            {
                TerrainIDPair tp{ t1,t2 };
                if (mBordersHorizontal.find(tp) == mBordersHorizontal.end())
                    mBordersHorizontal.insert({ tp,makePlaceholder(rng()) });
                if (mBordersVertical.find(tp) == mBordersVertical.end())
                    mBordersVertical.insert({ tp,makePlaceholder(rng()) });
            }
    }
}

NoiseModuleManager::~NoiseModuleManager()
{
}

const Reseedable NoiseModuleManager::getBorderVertical(TerrainID top, TerrainID bottom) const
{
    return mBordersVertical.at({ top,bottom });
}

const Reseedable NoiseModuleManager::getBorderHorizontal(TerrainID left, TerrainID right) const
{
    return mBordersHorizontal.at({ left,right });
}

Reseedable NoiseModuleManager::getStochastic(TerrainID terrain)
{
    return mStochasticMasks.at(terrain);
}
