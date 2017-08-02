#include <iostream>
#include <fstream>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/ConsoleAppender.h"
#include "logging/FileAppender.h"
#include "tilegen/TilesetGenerator.h"
#include "tilegen/TileGenerator.h"
#include "tilegen/partition/TilePartitionerNoise.h"

#include "OptionsManager.h"

namespace po = boost::program_options;

std::string usage(std::string program_path)
{
    return "Usage: " + program_path + " rel/path/to/options.json\n";
}

int main(int argc, char** argv)
{
    po::options_description cmd_options(usage(argv[0]) + "\nOptions:");
    logging::addAppender(std::make_unique<logging::ConsoleAppender>("console", logging::Level::Debug));

    cmd_options.add_options()
        ("help,h", "print usage")
        ("log-file", po::value<std::string>(), "write logs to a given file")
        ("options-file", po::value<std::string>()->required(),
            "input options file")
        ("verbose,v", "enable debug messages");

    po::positional_options_description positional_options;
    positional_options.add("options-file", -1);

    std::string filename;
    try
    {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                .options(cmd_options)
                .positional(positional_options)
                .run(), vm);

        if (vm.count("help"))
        {
            logInfo() << cmd_options;
            return 0;
        }
        po::notify(vm);

        if (vm.count("options-file"))
        {
            filename = vm["options-file"].as<std::string>();
        }

        const auto loggingLevel = vm.count("verbose") ? logging::Level::Debug : logging::Level::Info;
        logging::setLevel("console", loggingLevel);

        if (vm.count("log-file"))
        {
            const std::string logFile = vm["log-file"].as<std::string>();
            logging::addAppender(std::make_unique<logging::FileAppender>("file", logFile, loggingLevel));
        }
    }
    catch(const std::exception& e)
    {
        logError() << e.what() << "\n";
        logError() << cmd_options;
        return 1;
    }
    auto& optionsManager = getOptionsManager();
    optionsManager.loadOptions(filename);

    const Options& options = optionsManager.getOptions();
    
    std::unique_ptr<tilegen::partition::TilePartitionerBase> tp =
        std::make_unique<tilegen::partition::TilePartitionerNoise>(options);
    
    tilegen::TilesetGenerator tg(options, std::move(tp));
    
    tg.generate([](const sf::Texture& output, std::string filename)
    {
        const std::string image_dir = boost::filesystem::path(filename).remove_filename().string();
        boost::filesystem::create_directories(image_dir);
        if (!output.copyToImage().saveToFile(filename))
            throw std::runtime_error("Couldn't write image");
    });
    tg.metaOutput.writeAll(optionsManager.getOptions());

    return 0;
}
