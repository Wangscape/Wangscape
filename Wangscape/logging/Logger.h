#pragma once

#include "Appender.h"
#include "Level.h"

#include <string>
#include <map>
#include <memory>
#include <utility>
#include <vector>


namespace logging
{

template<Level level>
class Logger
{
public:
    Logger(std::vector<std::unique_ptr<Appender>>& appenders_)
        : mAppenders(appenders_)
    {}
    template<typename T>
    Logger& operator<<(T&& msg)
    {
        for (auto& appender : mAppenders)
            appender->log(msg, level);
        return *this;
    }
private:
    std::vector<std::unique_ptr<Appender>>& mAppenders;
};


} // namespace logging
