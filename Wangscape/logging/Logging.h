#pragma once

#include "AppenderType.h"
#include "Level.h"
#include "Logger.h"

#include <ostream>

#define LOG_ERROR getLogger(logging::Level::Error)
#define LOG_WARNING getLogger(logging::Level::Warning)
#define LOG_DEBUG getLogger(logging::Level::Debug)
#define LOG_INFO getLogger(logging::Level::Info)

namespace logging
{

void setLoggingLevel(Level level);
void setAppender(AppenderType appenderType, std::string name="");
Logger& getLogger(Level level);

} // namespace logging
