#include <iostream>
#include <fstream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <spotify/json.hpp>

#include "codecs/OptionsCodec.h"
#include "OptionsManager.h"
#include "TileGenerator.h"
#include "TilesetGenerator.h"

namespace po = boost::program_options;

std::string usage(std::string program_path)
{
    return "Usage: " + program_path + " rel/path/to/options.json\n";
}

int main(int argc, char** argv)
{
    po::options_description cmd_options(usage(argv[0]) + "\nOptions:");

    cmd_options.add_options()
        ("help,h", "print usage")
        ("options-file", po::value<std::string>()->required(),
            "input options file");

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
            std::cout << cmd_options;
            return 0;
        }
        po::notify(vm);

        if (vm.count("options-file"))
        {
            filename = vm["options-file"].as<std::string>();
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
        std::cout << cmd_options;
        return 1;
    }

    OptionsManager optionsManager(filename);

    TilesetGenerator tg(optionsManager.getOptions());
    tg.generate([](const sf::Texture& output, std::string filename)
    {
        if (!output.copyToImage().saveToFile(filename))
            throw std::runtime_error("Couldn't write image");
    });
    tg.mo.writeAll(optionsManager.getOptions());

    return 0;
}
