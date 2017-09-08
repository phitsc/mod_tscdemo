#pragma once

#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char divider)
{
    std::vector<std::string> result;

    std::string::size_type lastPos = 0;
    auto pos = s.find(divider);

    while (pos != std::string::npos)
    {
        result.push_back(s.substr(lastPos, pos - lastPos));

        lastPos = pos + 1;
        pos = s.find(divider, pos + 1);
    }

    if (lastPos <= s.size())
    {
        result.push_back(s.substr(lastPos));
    }

    return result;
}

