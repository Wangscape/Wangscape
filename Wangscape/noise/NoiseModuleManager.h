#pragma once
#include <memory>
#include <map>
#include <random>
#include <noise/noise.h>
#include "../common.h"
#include "module/Gradient.h"
#include "Reseedable.h"
#include "../Options.h"

namespace noise
{

class NoiseModuleManager
{
public:
    typedef noise::module::Module Module;
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;
    NoiseModuleManager(const Options& options);
    virtual ~NoiseModuleManager() = default;

    Reseedable getBorderVertical(TerrainID top, TerrainID bottom, bool x_positive);
    Reseedable getBorderHorizontal(TerrainID left, TerrainID right, bool y_positive);
    Reseedable& getStochastic(TerrainID terrain);
protected:
    std::mt19937 mRNG;

    // User-defined masks specifying how two corner terrain types
    // should blend in the region of horizontal border.
    // Evaluated in the square [0,1]x[0,1] (if the corners are at the bottom)
    // or [0,1]x[-1,0] (if the corners are at the top).
    // Reseeding will make terrain borders incompatible.
    std::map<TerrainIDPair, Reseedable> mBordersHorizontal;

    // User-defined masks specifying how two corner terrain types
    // should blend in the region of a vertical border.
    // Evaluated in the square [0,1]x[0,1] (if the corners are on the right)
    // or [-1,0]x[0,1] (if the corners are on the left).
    // Reseeding will make terrain borders incompatible.
    std::map<TerrainIDPair, Reseedable> mBordersVertical;

    // User-defined masks specifying how a corner terrain type
    // should blend with other corners in the region of the centre of the tile.
    // Evaluated in the square [0,1]x[0,1].
    // Normally evaluated with a different seed in every corner of every tile.
    std::map<TerrainID, Reseedable> mStochasticMasks;

};


} // namespace noise
