#pragma once

#include "ErrorUtils.h"

#include <format>
#include <stdexcept>
#include <utility>
#include <windows.h>

// =========================
// Shared local helpers
// =========================

namespace util
{
    inline void report_error(std::string_view msg,
        const char* func,
        const char* file,
        int line)
    {
        ::err::set_last_error(std::format("{} ({}:{})", msg, file, line));
        ::err::log_error(std::string(msg), func, file, line);
    }

    inline void report_warning(std::string_view msg,
        const char* func,
        const char* file,
        int line,
        bool setLastError = true)
    {
        if (setLastError)
        {
            ::err::set_last_error(std::format("{} ({}:{})", msg, file, line));
        }

        ::err::log_warn(std::string(msg), func, file, line);
    }

    inline std::string format_hresult_message(std::string_view msg, HRESULT hr)
    {
        return std::format("{} (HRESULT=0x{:08X})",
            msg,
            static_cast<unsigned long>(hr));
    }
}

// =========================
// Pointer validation macros
// =========================

#define ENSURE_VALID(ptr)                                                             \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}'", #ptr);             \
            ::util::report_error(__msg, __func__, __FILE__, __LINE__);                \
            return;                                                                   \
        }                                                                             \
    } while (0)

#define ENSURE_VALID_RET(ptr, retval)                                                 \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}'", #ptr);             \
            ::util::report_error(__msg, __func__, __FILE__, __LINE__);                \
            return (retval);                                                          \
        }                                                                             \
    } while (0)

#define CONTINUE_IF_INVALID(ptr)                                                      \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}' -> continuing loop", \
                                           #ptr);                                     \
            ::util::report_warning(__msg, __func__, __FILE__, __LINE__);              \
            continue;                                                                 \
        }                                                                             \
    } while (0)

#define BREAK_IF_INVALID(ptr)                                                         \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}' -> breaking", #ptr); \
            ::util::report_warning(__msg, __func__, __FILE__, __LINE__);              \
            break;                                                                    \
        }                                                                             \
    } while (0)

// =========================
// Get pointer/result macros
// =========================

// First use: declares `var`
#define DECL_GET_OR_RETURN(var, expr)                                                 \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg = std::format("Null pointer: '{}' returned null", #expr);    \
        ::util::report_error(__msg, __func__, __FILE__, __LINE__);                    \
        return;                                                                       \
    }

// Subsequent use: assigns into existing `var`
#define GET_OR_RETURN(var, expr)                                                      \
    do {                                                                              \
        (var) = (expr);                                                               \
        if (!(var)) {                                                                 \
            const auto __msg = std::format("Null pointer: '{}' returned null", #expr);\
            ::util::report_error(__msg, __func__, __FILE__, __LINE__);                \
            return;                                                                   \
        }                                                                             \
    } while (0)

#define DECL_GET_OR_RETURN_VAL(var, expr, retVal)                                     \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg = std::format("Null pointer: '{}' returned null", #expr);    \
        ::util::report_error(__msg, __func__, __FILE__, __LINE__);                    \
        return (retVal);                                                              \
    }

#define GET_OR_RETURN_VAL(var, expr, retVal)                                          \
    do {                                                                              \
        (var) = (expr);                                                               \
        if (!(var)) {                                                                 \
            const auto __msg = std::format("Null pointer: '{}' returned null", #expr);\
            ::util::report_error(__msg, __func__, __FILE__, __LINE__);                \
            return (retVal);                                                          \
        }                                                                             \
    } while (0)

#define DECL_GET_OR_CONTINUE(var, expr)                                               \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg =                                                            \
            std::format("Null pointer: '{}' returned null -> continuing loop", #expr);\
        ::util::report_warning(__msg, __func__, __FILE__, __LINE__);                  \
        continue;                                                                     \
    }

#define DECL_GET_OR_BREAK(var, expr)                                                  \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg =                                                            \
            std::format("Null pointer: '{}' returned null -> breaking", #expr);       \
        ::util::report_warning(__msg, __func__, __FILE__, __LINE__);                  \
        break;                                                                        \
    }

// =========================
// Exception-handling macro
// =========================

#define ERR_TRY_ASSIGN_OR_RET(target, expr, retval)                                   \
    do {                                                                              \
        try {                                                                         \
            (target) = (expr);                                                        \
        } catch (const std::exception& e) {                                           \
            const auto __msg = std::format("Exception in '{}': {}", #expr, e.what()); \
            ::util::report_error(__msg, __func__, __FILE__, __LINE__);                \
            return (retval);                                                          \
        }                                                                             \
    } while (0)

// =========================
// HRESULT helpers
// =========================

#define HR_CHECK(hr, msg)                                                             \
    do {                                                                              \
        const HRESULT __hr = (hr);                                                    \
        if (FAILED(__hr)) {                                                           \
            const auto __err = ::util::format_hresult_message((msg), __hr);           \
            ::util::report_error(__err, __func__, __FILE__, __LINE__);                \
            MessageBoxA(nullptr, __err.c_str(), "HRESULT failure", MB_OK | MB_ICONERROR); \
            return 0;                                                                 \
        }                                                                             \
    } while (0)

#define HR_THROW_IF_FAILED(hr, msg)                                                   \
    do {                                                                              \
        const HRESULT __hr = (hr);                                                    \
        if (FAILED(__hr)) {                                                           \
            const auto __err = ::util::format_hresult_message((msg), __hr);           \
            ::util::report_error(__err, __func__, __FILE__, __LINE__);                \
            throw std::runtime_error(__err);                                          \
        }                                                                             \
    } while (0)

#define HR_LOG_AND_RET(hr, msg, retval)                                               \
    do {                                                                              \
        const HRESULT __hr = (hr);                                                    \
        if (FAILED(__hr)) {                                                           \
            const auto __err = ::util::format_hresult_message((msg), __hr);           \
            ::util::report_error(__err, __func__, __FILE__, __LINE__);                \
            return (retval);                                                          \
        }                                                                             \
    } while (0)

// =========================
// Utility callable
// =========================

struct ToIntFn
{
    template <typename E>
    constexpr int operator()(E e) const noexcept
    {
        return static_cast<int>(e);
    }
};

extern const ToIntFn ToInt;