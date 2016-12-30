#pragma once

#include "Options.h"

class OptionsManager
{
public:
    OptionsManager() = default;
    OptionsManager(std::string filename);
    void loadOptions(std::string filename);
    void createOutputDirectory(std::string filename);
    const Options& getOptions() const;

private:
    Options mOptions;
};

