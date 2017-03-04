#pragma once
#include <string>
class OptionsPaths
{
public:
    virtual ~OptionsPaths();
    void initialise(std::string filename);
    std::string filename;
    std::string directory;
};

