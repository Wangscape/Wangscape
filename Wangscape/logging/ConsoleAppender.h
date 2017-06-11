#pragma once

#include <iostream>

#include "Appender.h"

namespace logging
{

class ConsoleAppender : public Appender
{
public:
    using Appender::Appender;
    virtual std::ostream& getStream() override;
};

} // namespace logging
