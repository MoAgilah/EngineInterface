#pragma once

#include <filesystem>
#include <fstream>

namespace TestHelpers
{
    inline std::filesystem::path GetTempFilePath()
    {
        return std::filesystem::temp_directory_path() /
            ("logger_test_" + std::to_string(std::rand()) + "_" +
                std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
                ".txt");
    }

    inline std::string ReadFile(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        return std::string((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
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
