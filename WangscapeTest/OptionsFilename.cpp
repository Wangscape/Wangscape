#include "OptionsFilename.h"
#include <stdexcept>

namespace
{
std::string filename;
bool filenameSet = false;
}

const std::string& getOptionsFilename()
{
    return filename;
}

void setOptionsFilename(const std::string & optionsFilename)
{
    if (filenameSet)
        throw std::runtime_error("Options filename already set");
    filename = optionsFilename;
    filenameSet = true;
}
