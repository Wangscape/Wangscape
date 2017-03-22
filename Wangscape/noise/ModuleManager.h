#pragma once
#include <memory>
#include <map>
#include <random>

#include "common.h"
#include "Options.h"
#include "ModuleGroupContainer.h"

namespace noise
{

class ModuleManager
{
public:
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;

    explicit ModuleManager(const Options& options);
    virtual ~ModuleManager() = default;

    ModuleGroup& getTopBorder(TerrainID top, TerrainID bottom);
    ModuleGroup& getLeftBorder(TerrainID left, TerrainID right);
    ModuleGroup& getBottomRightBorder();
    ModuleGroup& getCentral(TerrainID terrain);
    ModuleGroup& getCombiner();
private:
    std::mt19937 mRNG;

    // User-defined masks specifying how two corner terrain types
    // should blend in the region of horizontal border.
    // Evaluated in the square [0,1]x[0,1] (if the corners are at the bottom)
    // or [0,1]x[-1,0] (if the corners are at the top).
    // Reseeding will make terrain borders incompatible.
    ModuleGroupContainer<TerrainIDPair> mLeftBorders;

    // User-defined masks specifying how two corner terrain types
    // should blend in the region of a vertical border.
    // Evaluated in the square [0,1]x[0,1] (if the corners are on the right)
    // or [-1,0]x[0,1] (if the corners are on the left).
    // Reseeding will make terrain borders incompatible.
    ModuleGroupContainer<TerrainIDPair> mTopBorders;

    // User-defined masks specifying how a corner terrain type
    // should blend with other corners in the region of the centre of the tile.
    // Evaluated in the square [0,1]x[0,1].
    // Normally evaluated with a different seed in every corner of every tile.
    ModuleGroupContainer<TerrainID> mCentres;

    std::shared_ptr<ModuleGroup> mBottomRightBorder;

    std::shared_ptr<ModuleGroup> mCombiner;
};

} // namespace noise
