#include "TestRequiringOptions.h"

TestRequiringOptions::TestRequiringOptions() :
    filename("Wangscape/example/example_options.json"),
    optionsManager(filename),
    options(optionsManager.getOptions())
{
}
