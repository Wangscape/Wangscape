#include <iostream>

#include "FileAppender.h"

namespace logging
{

FileAppender::FileAppender(std::string name_, std::string filename_, Level level_)
    : Appender(name_, level_)
{
    mOutStream.open(filename_);
}

std::ostream& FileAppender::getStream()
{
    return mOutStream;
}

} // namespace logging
