#pragma once

#include "Level.h"

#include <string>


namespace logging
{

class Logger
{
public:
    Logger() = default;
    explicit Logger(std::ostream* out_)
        : mAppender{out_}
    {
    }
    void setStream(std::ostream* out)
    {
        mAppender = out;
    }
    template<typename T>
    Logger& operator<<(T&& msg)
    {
        if (mAppender != nullptr) {
            *mAppender << std::forward<T>(msg);
        }
        return *this;
    }
private:
    std::ostream* mAppender = nullptr;
};


} // namespace logging
