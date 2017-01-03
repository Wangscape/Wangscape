#include <gtest/gtest.h>
#include "TestRequiringOptions.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::string filename;
    if (argc < 2)
        filename = std::string("Wangscape/example/example_options.json");
    else
        filename = std::string(argv[1]);
    std::cout << "Using options file at " << filename << "\n";
    assert(TestRequiringOptions::initFilename(filename));
    return RUN_ALL_TESTS();
} 
