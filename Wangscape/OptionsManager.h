#pragma once

#include "Options.h"

class OptionsManager
{
public:
    OptionsManager() = default;
    OptionsManager(std::string optionsFilename);
    void loadOptions(std::string optionsFilename);
    void createOutputDirectory(std::string filename);
    const Options& getOptions() const;

private:
    Options mOptions;
};

