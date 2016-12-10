#include <iostream>
#include "Options.h"
#include "TilesetGenerator.h"
#include "TileGenerator.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: Wangscape rel/path/to/options.json\n";
        exit(1);
    }
    else
    {
        std::string filename(argv[1]);

        const Options options(filename);
        TilesetGenerator tg(options);
        tg.generate([](const sf::Texture& output, std::string filename)
        {
            if (!output.copyToImage().saveToFile(filename))
                throw std::runtime_error("Couldn't write image");
        });
        tg.mo.writeAll(options);
    }
}