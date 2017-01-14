#include "OptionsManager.h"

#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>

#include <spotify/json.hpp>

#include "codecs/OptionsCodec.h"

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
    catch (spotify::json::decode_exception e)
    {
        std::cout << "spotify::json::decode_exception encountered at "
            << e.offset()
            << ": "
            << e.what();
        throw;
    }
    mOptions.filename = optionsFilename;

    createOutputDirectory(optionsFilename);
}

void OptionsManager::createOutputDirectory(std::string optionsFilename)
{
    // TODO(hryniuk): move it elsewhere
    auto outputDirectory = mOptions.outputDirectory;
    boost::filesystem::path p(optionsFilename);
    p.remove_filename();
    p.append(outputDirectory);
    boost::filesystem::create_directories(p);
    auto relativeOutputDirectory = p.string();
    mOptions.relativeOutputDirectory = relativeOutputDirectory;
}

const Options& OptionsManager::getOptions() const
{
    return mOptions;
}

