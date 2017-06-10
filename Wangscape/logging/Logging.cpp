#include "Appender.h"
#include "Level.h"
#include "Logging.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>


logging::Logger<logging::Level::Debug> logDebug()
{
    return logging::log<logging::Level, logging::Level::Debug>();
}

logging::Logger<logging::Level::Info> logInfo()
{
    return logging::log<logging::Level, logging::Level::Info>();
}

logging::Logger<logging::Level::Warning> logWarning()
{
    return logging::log<logging::Level, logging::Level::Warning>();
}

logging::Logger<logging::Level::Error> logError()
{
    return logging::log<logging::Level, logging::Level::Error>();
}


namespace logging
{

namespace
{

std::vector<std::unique_ptr<Appender>> appenders;

} // anonymous namespace

void addAppender(std::unique_ptr<Appender> appender)
{
    appenders.push_back(std::move(appender));
}

void setLevel(std::string appender_name, logging::Level new_level)
{
    for (auto& appender : appenders)
    {
        if (appender->getName() == appender_name)
        {
            appender->setLevel(new_level);
        }
    }
}

template<typename LevelEnum, LevelEnum Level>
Logger<Level> log()
{
    return Logger<Level>{appenders};
}

} // namespace logging
