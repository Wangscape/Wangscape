#include "ConsoleAppender.h"

namespace logging
{

std::ostream& ConsoleAppender::getStream()
{
    return std::cout;
}

} // namespace logging
