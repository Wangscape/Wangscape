#include "OptionsPaths.h"
#include <boost/filesystem/path.hpp>

OptionsPaths::~OptionsPaths()
{
}

void OptionsPaths::initialise(std::string filename)
{
    this->filename = filename;
    directory = boost::filesystem::path(filename).parent_path().string();
}
