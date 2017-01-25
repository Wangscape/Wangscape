#include "TestRequiringOptions.h"
#include "OptionsFilename.h"

TestRequiringOptions::TestRequiringOptions() :
    optionsFilename(getOptionsFilename()),
    optionsManager(optionsFilename),
    options(optionsManager.getOptions())
{
}