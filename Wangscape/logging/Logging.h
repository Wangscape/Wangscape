#pragma once

#include "Level.h"
#include "Logger.h"

#include <ostream>

logging::Logger<logging::Level::Debug> logDebug();
logging::Logger<logging::Level::Info> logInfo();
logging::Logger<logging::Level::Warning> logWarning();
logging::Logger<logging::Level::Error> logError();

namespace logging
{

void addAppender(std::unique_ptr<Appender> appender);
void setLevel(std::string appender_name, logging::Level new_level);
template<typename LevelEnum, LevelEnum Level>
Logger<Level> log();

} // namespace logging
