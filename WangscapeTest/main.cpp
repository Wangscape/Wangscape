#include <gtest/gtest.h>
#include "DocumentationPath.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::string doc_path;
    if (argc < 2)
        doc_path = std::string("doc");
    else
        doc_path = std::string(argv[1]);
    std::cout << "Using documentation directory at " << doc_path << "\n";
    setDocumentationPath(doc_path);
    return RUN_ALL_TESTS();
} 
