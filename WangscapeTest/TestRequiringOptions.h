#pragma once

#include <gtest/gtest.h>

#include <Options.h>
#include <OptionsManager.h>

class TestRequiringOptions : public ::testing::Test {
protected:
    std::string filename;
    const Options& options;
    const OptionsManager optionsManager;

    TestRequiringOptions();
    virtual ~TestRequiringOptions() = default;
};