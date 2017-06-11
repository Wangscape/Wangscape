#pragma once

#include <iostream>

#include "Level.h"

namespace logging
{

class Appender
{
public:
    Appender(std::string name_, Level min_level_)
        : mName(name_), mMinLevel{min_level_}
    {
    }
    virtual ~Appender() = default;
    std::string getName() const
    {
        return mName;
    }
    void setLevel(Level new_level)
    {
        mMinLevel = new_level;
    }
    template<typename T>
    Appender& log(T&& t, Level level)
    {
        if (level >= mMinLevel)
            getStream() << t;
        return *this;
    }
    virtual std::ostream& getStream() = 0;
private:
    std::string mName;
    Level mMinLevel;
};

} // namespace logging
