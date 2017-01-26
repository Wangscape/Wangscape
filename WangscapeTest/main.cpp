#include <gtest/gtest.h>
#include "OptionsFilename.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::string filename;
    if (argc < 2)
        filename = std::string("Wangscape/example/example_options.json");
    else
        filename = std::string(argv[1]);
    std::cout << "Using options file at " << filename << "\n";
    setOptionsFilename(filename);
    return RUN_ALL_TESTS();
} 
