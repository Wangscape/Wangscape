#include "OptionsManager.h"

#include <fstream>

#include <boost/filesystem.hpp>

#include <spotify/json.hpp>

#include "codecs/OptionsCodec.h"

OptionsManager::OptionsManager(std::string filename)
{
    loadOptions(filename);

    // TODO(hryniuk): move it elsewhere
    auto outputDirectory = mOptions.outputDirectory;
    boost::filesystem::path p(filename);
    p.remove_filename();
    p.append(outputDirectory);
    boost::filesystem::create_directories(p);
    auto relativeOutputDirectory = p.string();
    mOptions.relativeOutputDirectory = relativeOutputDirectory;
}

void OptionsManager::loadOptions(std::string filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not open options file");
    }

    std::string str{std::istreambuf_iterator<char>(ifs),
                    std::istreambuf_iterator<char>()};

    mOptions = spotify::json::decode<Options>(str.c_str());
    mOptions.filename = filename;
}

const Options& OptionsManager::getOptions() const
{
    return mOptions;
}

