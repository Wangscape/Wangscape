#pragma once

#include "Appender.h"

#include <iostream>
#include <fstream>

namespace logging
{

class FileAppender : public Appender
{
public:
    FileAppender(std::string name_, std::string filename_, Level level_=Level::Info);
    virtual std::ostream& getStream() override;
private:
    std::ofstream mOutStream;
};

} // namespace logging
