#pragma once

#include <string>

class IFont
{
public:
    virtual ~IFont() = default;
    virtual bool LoadFromFile(const std::string& filepath) = 0;
};
