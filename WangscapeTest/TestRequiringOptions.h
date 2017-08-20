#pragma once

#include <gtest/gtest.h>

#include <Options.h>
#include <OptionsManager.h>

class TestRequiringOptions : public ::testing::Test
{
public:
protected:
    const std::string optionsFilename;
    const Options& options() const;
    TestRequiringOptions();
    virtual ~TestRequiringOptions() = default;
};