#pragma once

#include "Logger.h"

#include <Windows.h>
#include <format>
#include <source_location>
#include <stdexcept>
#include <string>

inline bool CheckHResult(
    HRESULT hr,
    const std::string& msg,
    const std::source_location& loc = std::source_location::current())
{
    if (SUCCEEDED(hr))
        return true;

    const auto err = std::format(
        "{} (HRESULT=0x{:08X})",
        msg,
        static_cast<unsigned long>(hr));

    Logger::GetDefaultLogger().Log(LogLevel::Error, err, loc);
    return false;
}

inline void ThrowIfHResultFailed(
    HRESULT hr,
    const std::string& msg,
    const std::source_location& loc = std::source_location::current())
{
    if (SUCCEEDED(hr))
        return;

    const auto err = std::format(
        "{} (HRESULT=0x{:08X})",
        msg,
        static_cast<unsigned long>(hr));

    Logger::GetDefaultLogger().Log(LogLevel::Error, err, loc);
    throw std::runtime_error(err);
}