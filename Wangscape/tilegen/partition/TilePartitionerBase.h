#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "Options.h"
#include <boost/optional.hpp>
#include <noise/module/ModulePtr.h>
#include "tilegen/DebugTilesetID.h"

namespace tilegen
{
namespace partition
{

class TilePartitionerBase
{
public:
    typedef std::vector<std::pair<sf::Texture, TerrainID>> TilePartition;
    typedef std::vector<TerrainID> Corners;
    typedef std::function<void(const DebugTilesetID&, noise::module::ModulePtr)> DebugModuleWriter;

    explicit TilePartitionerBase(const Options& options);
    virtual ~TilePartitionerBase() = default;
    virtual void makePartition(TilePartition& regions, const Corners& corners) = 0;
    void setDebugModuleWriter(DebugModuleWriter debugModuleWriter);
protected:
    DebugModuleWriter mDebugModuleWriter;
    const Options& mOptions;
};

} // namespace partition
} // namespace tilegen
