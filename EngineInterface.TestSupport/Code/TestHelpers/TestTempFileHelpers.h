#pragma once

#include <filesystem>

namespace TestHelpers
{
    inline std::filesystem::path GetTempFilePath()
    {
        return std::filesystem::temp_directory_path() /
            ("logger_test_" + std::to_string(std::rand()) + "_" +
                std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
                ".txt");
    }

    struct TempFileGuard
    {
        std::filesystem::path path{ GetTempFilePath() };

        TempFileGuard() = default;
        explicit TempFileGuard(std::filesystem::path p) : path(std::move(p)) {}

        TempFileGuard(const TempFileGuard&) = delete;
        TempFileGuard& operator=(const TempFileGuard&) = delete;

        TempFileGuard(TempFileGuard&&) = default;
        TempFileGuard& operator=(TempFileGuard&&) = default;

        ~TempFileGuard()
        {
            if (!path.empty() && std::filesystem::exists(path))
            {
                std::filesystem::remove(path);
            }
        }
    };
}
