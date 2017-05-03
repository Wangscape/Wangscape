#pragma once

#include <string>
#include "Options.h"
#include <boost/filesystem.hpp>
#include "noise/RasterImage.h"
#include "noise/module/ModulePtr.h"
#include "TilePartitionerBase.h"
#include "noise/ModuleGroup.h"

namespace tilegen
{
namespace partition
{

class DebugWriter
{
public:
    DebugWriter(const Options& options_);
    virtual ~DebugWriter() = default;
    void setTerrains(const TilePartitionerBase::Corners& corners);
    void setCorner(bool top, bool left);
    void writeDebugMap(const noise::module::ModulePtr module, std::string filename);
    void writeDebugGroup(const noise::ModuleGroup & mg, std::string mg_name);
    std::string getCornerDescription() const;
private:
    const Options& mOptions;
    boost::filesystem::path mDebugDir;
    boost::filesystem::path mDebugSubDir;
    std::string mTerrains;
    std::string mCorner;
    sf::Image mImage;
    noise::RasterImage mRaster;
};

}
}

