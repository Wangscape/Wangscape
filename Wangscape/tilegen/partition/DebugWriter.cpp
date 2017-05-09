#include "DebugWriter.h"

namespace tilegen
{
namespace partition
{

DebugWriter::DebugWriter(const Options& options_) :
    mOptions(options_),
    mDebugDir(mOptions.paths.directory),
    mRaster(mImage, noise::RasterBase::Bounds(0, 0, 1, 1))
{
    mDebugDir /= mOptions.outputDirectory;
    mDebugDir /= "debug";
    if (mOptions.debugTileResolution)
    {
        mImage.create(mOptions.debugTileResolution->first, mOptions.debugTileResolution->second);
    }
    else
    {
        mImage.create(mOptions.tileFormat.resolution.x * 8, mOptions.tileFormat.resolution.y * 8);
    }
}

void DebugWriter::setCorner(bool top, bool left)
{
    mCorner = top ? "T" : "B";
    mCorner += left ? "L" : "R";
}

void DebugWriter::setTerrains(const TilePartitionerBase::Corners& corners)
{
    mTerrains = "";
    for (auto terrain_id : corners)
    {
        mTerrains += terrain_id;
        mTerrains += ".";
    }
}

void DebugWriter::writeDebugMap(const noise::module::ModulePtr module, std::string filename)
{
    mRaster.build(module->getModule());
    mImage.saveToFile((mDebugSubDir / (filename + ".png")).string());
}
void DebugWriter::writeDebugGroup(const noise::ModuleGroup & mg, std::string mg_name)
{
    mDebugSubDir = mDebugDir / getCornerDescription();
    boost::filesystem::create_directories(mDebugSubDir);
    for (auto it : mg.getModules())
    {
        writeDebugMap(it.second, mg_name + "_" + it.first);
    }
}

std::string DebugWriter::getCornerDescription() const
{
    return mTerrains + mCorner;
}

}
}
