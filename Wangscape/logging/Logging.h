#pragma once

#include "AppenderType.h"
#include "Level.h"
#include "Logger.h"

#include <ostream>

logging::Logger& logDebug();
logging::Logger& logInfo();
logging::Logger& logWarning();
logging::Logger& logError();

namespace logging
{

void setLoggingLevel(Level level);
void setAppender(AppenderType appenderType, std::string name="");
Logger& getLogger(Level level);

} // namespace logging
