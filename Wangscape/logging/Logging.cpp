#include "Level.h"
#include "Logging.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

namespace logging
{

namespace
{

std::ofstream out;
Level currentLevel = Level::Info;
Logger noopLogger;
Logger currentLogger(&std::cout);

} // anonymous namespace

void setAppender(AppenderType appenderType, std::string name)
{
    switch (appenderType)
    {
        case AppenderType::StdOut:
        {
            currentLogger.setStream(&std::cout);
            break;
        }
        case AppenderType::StdErr:
        {
            currentLogger.setStream(&std::cerr);
            break;
        }
        case AppenderType::File:
        {
            if (out.is_open()) {
                out.close();
            }
            out.open(name, std::ios_base::app);
            currentLogger.setStream(&out);
            break;
        }
        default:
        {
            currentLogger.setStream(&std::cout);
        }
    }
}

void setLoggingLevel(Level level)
{
    currentLevel = level;
}

Logger& getLogger(Level level)
{
    if (level < currentLevel)
    {
        return noopLogger;
    }
    return currentLogger;
}

} // namespace logging
