#include "TestRequiringOptions.h"
#include "DocumentationPath.h"
#include <boost/filesystem.hpp>

TestRequiringOptions::TestRequiringOptions() :
    optionsFilename((boost::filesystem::path(getDocumentationPath()) /
                     "examples" / "example2" / "example_options.json").string()),
    optionsManager(optionsFilename),
    options(optionsManager.getOptions())
{
}