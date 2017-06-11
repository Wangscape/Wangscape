#include "OptionsManager.h"

#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>

#include <spotify/json.hpp>

#include "codecs/OptionsCodec.h"
#include "logging/Logging.h"

OptionsManager::OptionsManager(std::string optionsFilename)
{
    loadOptions(optionsFilename);
}

void OptionsManager::loadOptions(std::string optionsFilename)
{
    std::ifstream ifs(optionsFilename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not open options file");
    }

    std::string str{std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()};
    try
    {
        mOptions = spotify::json::decode<Options>(str.c_str());
    }
    catch (const spotify::json::decode_exception& e)
    {
        logError() << "spotify::json::decode_exception encountered at "
            << e.offset()
            << ": "
            << e.what();
        throw;
    }
    mOptions.paths.initialise(optionsFilename);
    createOutputDirectory();
}

void OptionsManager::createOutputDirectory()
{
    // TODO(hryniuk): move it elsewhere
    boost::filesystem::path p(mOptions.paths.directory);
    p.append(mOptions.outputDirectory);
    auto relativeOutputDirectory = p.string();
    mOptions.relativeOutputDirectory = relativeOutputDirectory;
}

const Options& OptionsManager::getOptions() const
{
    return mOptions;
}

