#pragma once

#include <Utilities/Logger.h>
#include <filesystem>

namespace TestHelpers
{
    inline void CleanupDefaultLoggerForTests()
    {
        if (::Logger::s_defaultLoggerInitialised)
        {
            const std::string logPath = ::Logger::s_defaultLogPath;

            ::Logger::GetDefaultLogger().Stop();

            if (!logPath.empty())
            {
                std::error_code ec;
                std::filesystem::remove(logPath, ec);
            }
        }

        ::Logger::s_defaultLogPath.clear();
        ::Logger::s_defaultLoggerInitialised = false;
    }
}