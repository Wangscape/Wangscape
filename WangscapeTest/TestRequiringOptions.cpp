#include <gtest/gtest.h>

#include <Options.h>
#include <OptionsManager.h>

class TestRequiringOptions : public ::testing::Test {
protected:
    std::string filename;
    const Options& options;
    const OptionsManager optionsManager;

    TestRequiringOptions() :
        filename("../../Wangscape/example/example_options.json"),
        optionsManager(filename),
        options(optionsManager.getOptions())
    {
    };
   virtual ~TestRequiringOptions() = default;
};