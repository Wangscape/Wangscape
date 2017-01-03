#pragma once

#include <gtest/gtest.h>

#include <Options.h>
#include <OptionsManager.h>

class TestRequiringOptions : public ::testing::Test
{
public:
    static bool initFilename(std::string filename);
protected:
    const Options& options;
    const OptionsManager optionsManager;

    TestRequiringOptions();
    virtual ~TestRequiringOptions() = default;
    static const std::string& getFilename();
private:
    static std::string mFilename;
    static bool mFilenameSet;
};