#include "removeWhitespace.h"

#include <algorithm>
#include <locale>

void removeWhitespace(std::string& s)
{
    s.erase(std::remove_if(s.begin(),
                           s.end(),
                           [](char c) { return std::isspace(c, std::locale()); }),
            s.end());
}