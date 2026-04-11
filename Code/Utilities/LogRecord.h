#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <source_location>

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
};

inline const char* toString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:   return "DEBUG";
    case LogLevel::Info:    return "INFO";
    case LogLevel::Warning: return "WARNING";
    case LogLevel::Error:   return "ERROR";
    case LogLevel::Fatal:   return "FATAL";
    }

    return "UNKNOWN";
}

struct SourceInfo
{
    explicit SourceInfo(const std::source_location& loc)
        : file(loc.file_name()),
        line(static_cast<int>(loc.line())),
        column(static_cast<int>(loc.column())),
        function(loc.function_name())
    {}

    std::string file;
    int line;
    int column;
    std::string function;
};

struct ThreadInfo
{
    std::thread::id id;
    std::string optional_thread_label;
};

struct LogRecord
{
    LogRecord(
        LogLevel logLevel,
        std::string message,
        const std::source_location& loc)
        : timestamp(std::chrono::system_clock::now()),
        logLevel(logLevel),
        message(std::move(message)),
        sourceInfo(loc)
    {}

	std::chrono::system_clock::time_point timestamp;
    LogLevel logLevel;
    std::string message;
    SourceInfo sourceInfo;
    ThreadInfo threadInfo;
    uint64_t sequenceId = 0;
};