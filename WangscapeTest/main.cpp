#include <gtest/gtest.h>
#include "TestRequiringOptions.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    assert(TestRequiringOptions::initFilename("Wangscape/example/example_options.json"));
    return RUN_ALL_TESTS();
}