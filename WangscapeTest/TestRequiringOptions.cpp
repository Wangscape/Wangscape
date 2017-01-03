#include "TestRequiringOptions.h"

bool TestRequiringOptions::initFilename(std::string filename)
{
    if(mFilenameSet)
        return false;
    mFilename = filename;
    mFilenameSet = true;
    return true;
}

TestRequiringOptions::TestRequiringOptions() :
    optionsManager(mFilename),
    options(optionsManager.getOptions())
{
}

const std::string & TestRequiringOptions::getFilename()
{
    return mFilename;
}

bool TestRequiringOptions::mFilenameSet;
std::string TestRequiringOptions::mFilename;