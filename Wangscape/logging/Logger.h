#pragma once

#include "Level.h"

#include <string>


namespace logging
{

class Logger
{
public:
    Logger() = default;
    explicit Logger(std::ostream* out)
        : appender_{out}
    {
    }
    void setStream(std::ostream* out)
    {
        appender_ = out;
    }
    template<typename T>
    Logger& operator<<(T&& msg)
    {
        if (appender_ != nullptr) {
            *appender_ << msg;
        }
        return *this;
    }
private:
    std::ostream* appender_ = nullptr;
};


} // namespace logging
