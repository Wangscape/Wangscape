#include "Options.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <stdexcept>
#include <boost/filesystem.hpp>

Options::Options(std::string filename):
    filename(filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not read options file");
    }
    std::string str{std::istreambuf_iterator<char>(ifs),
                    std::istreambuf_iterator<char>()};
}
