#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>
#include <format>
#include <stdexcept>
#include <utility>

namespace err {

    // ---------- configurable log file ----------
    inline std::string& log_path() {
        static std::string p = "error.log";
        return p;
    }
    inline void set_log_file(std::string path) { log_path() = std::move(path); }

    // ---------- per-thread last-error storage ----------
    inline thread_local std::string g_last_error; // empty when no error set

    inline void set_last_error(std::string msg) { g_last_error = std::move(msg); }
    inline const std::string& last_error() { return g_last_error; }
    inline std::string take_last_error() { std::string t; t.swap(g_last_error); return t; }
    inline void clear_last_error() { g_last_error.clear(); }

    // ---------- time + logging ----------
    inline std::string now_utc_iso8601() {
        using namespace std::chrono;
        const auto t = system_clock::now();
        const auto tt = system_clock::to_time_t(t);
        std::tm tm{};
#if defined(_WIN32)
        gmtime_s(&tm, &tt);
#else
        gmtime_r(&tt, &tm);
#endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

    inline void log_line(const char* level,
        const std::string& msg,
        const char* func,
        const char* file,
        int line)
    {
        std::ofstream out(log_path(), std::ios::app);
        out << std::format("{} [{}] {} | {} ({}:{})\n",
            now_utc_iso8601(), level, msg, func, file, line);
    }

    inline void log_error(const std::string& msg,
        const char* func,
        const char* file,
        int line)
    {
        log_line("ERROR", msg, func, file, line);
    }

    inline void log_warn(const std::string& msg,
        const char* func,
        const char* file,
        int line)
    {
        log_line("WARN", msg, func, file, line);
    }

} // namespace err

// Default message
#define THROW_IF_FALSE(expr)                                                          \
    do {                                                                              \
        if (!(expr)) {                                                                \
            const auto __msg = std::format("Expression '{}' failed", #expr);          \
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_error(__msg, __func__, __FILE__, __LINE__);                    \
            throw std::runtime_error(__msg);                                          \
        }                                                                             \
    } while (0)

// Custom (works with 1+ args): e.g.
// THROW_IF_FALSE_MSG(Init(), "SFText initialization failed");
// THROW_IF_FALSE_MSG(shader, "Shader '{}' not found", "FadeInOutShader");
#define THROW_IF_FALSE_MSG(expr, ...)                                                 \
    do {                                                                              \
        if (!(expr)) {                                                                \
            const auto __extra = std::format(__VA_ARGS__);                            \
            const auto __msg   = std::format("Expression '{}' failed: {}", #expr, __extra); \
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_error(__msg, __func__, __FILE__, __LINE__);                    \
            throw std::runtime_error(__msg);                                          \
        }                                                                             \
    } while (0)

