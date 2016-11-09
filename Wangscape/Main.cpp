#include <iostream>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <fstream>
#include <istream>
#include "Options.h"
#include "TilesetGenerator.h"

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
        std::ifstream ifs(filename);
        if (!ifs.good())
        {
            std::cout << "Could not read file: " << filename.c_str() << "\n";
            exit(1);
        }
        rapidjson::IStreamWrapper isw(ifs);
        rapidjson::Document options_document;
        options_document.ParseStream(isw);
        if (options_document.HasParseError())
        {
            std::cout << "Options document has parse error at offset "<< (unsigned)options_document.GetErrorOffset() <<":\n";
            std::cout << GetParseError_En(options_document.GetParseError()) << "\n";
        }
        // At present *no* validation is performed!
        //OptionsValidator tg(&options);
        //if (tg.hasError())
        //{
        //    std::cout << "Could not generate tileset.\n";
        //    std::cout << tg.getError().c_str();
        //}
        Options options(options_document);
        TilesetGenerator tg(options);
    }
}