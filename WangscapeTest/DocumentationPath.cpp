#include "DocumentationPath.h"
#include <stdexcept>

namespace
{
std::string documentationPath;
bool docPathSet = false;
}

const std::string& getDocumentationPath()
{
    return documentationPath;
}

void setDocumentationPath(const std::string & doc_path)
{
    if (docPathSet)
    {
        throw std::runtime_error("Documentation path already set");
    }
    else
    {
        documentationPath = doc_path;
        docPathSet = true;
    }
}
