#pragma once

#include "Options.h"

class OptionsManager
{
public:
    OptionsManager() = default;
    OptionsManager(std::string optionsFilename);
    void loadOptions(std::string optionsFilename);
    void createOutputDirectory();
    const Options& getOptions() const;

private:
    Options mOptions;
};

OptionsManager& getOptionsManager();
