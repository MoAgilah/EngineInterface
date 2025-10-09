#pragma once

#include "ErrorUtils.h"

#include <iostream>

// =========================
// Pointer validation macros
// =========================

#define ENSURE_VALID(ptr)                                                             \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}'", #ptr);             \
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_error(__msg, __func__, __FILE__, __LINE__);                    \
            return;                                                                   \
        }                                                                             \
    } while (0)

#define ENSURE_VALID_RET(ptr, retval)                                                 \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}'", #ptr);             \
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_error(__msg, __func__, __FILE__, __LINE__);                    \
            return (retval);                                                          \
        }                                                                             \
    } while (0)

#define CONTINUE_IF_INVALID(ptr)                                                      \
    do {                                                                              \
        if (!(ptr)) {                                                                 \
            const auto __msg = std::format("Invalid pointer '{}' -> continuing loop", #ptr); \
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_warn(__msg, __func__, __FILE__, __LINE__);                     \
            continue;                                                                 \
        }                                                                             \
    } while (0)

#define GET_OR_RETURN(var, expr)                                                      \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg = std::format("Null pointer: '{}' returned null", #expr);    \
        ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__));  \
        ::err::log_error(__msg, __func__, __FILE__, __LINE__);                        \
        return;                                                                       \
    }

// GET_OR_CONTINUE: declare var from expr; if null -> warn + continue
#define GET_OR_CONTINUE(var, expr)                                                    \
        auto var = (expr);                                                            \
        if (!(var)) {                                                                 \
            const auto __msg = std::format("Null pointer: '{}' returned null -> continuing loop", #expr); \
            ::err::log_warn(__msg, __func__, __FILE__, __LINE__);                     \
            return;                                                                 \
        }                                                                             \

// Optional: switch-friendly
#define GET_OR_BREAK(var, expr)                                                       \
    auto var = (expr);                                                                \
    if (!(var)) {                                                                     \
        const auto __msg = std::format("Null pointer: '{}' returned null", #expr);    \
        ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__));  \
        ::err::log_warn(__msg, __func__, __FILE__, __LINE__);                         \
        break;                                                                        \
    }

// Optional: try/assign + return for bool functions, etc.
#define ERR_TRY_ASSIGN_OR_RET(target, expr, retval)                                   \
    do {                                                                              \
        try {                                                                         \
            (target) = (expr);                                                        \
        } catch (const std::exception& e) {                                           \
            const auto __msg = std::format("Exception in '{}': {}", #expr, e.what());\
            ::err::set_last_error(std::format("{} ({}:{})", __msg, __FILE__, __LINE__)); \
            ::err::log_error(__msg, __func__, __FILE__, __LINE__);                    \
            return (retval);                                                          \
        }                                                                             \
    } while (0)


struct ToIntFn
{
    template <typename E>
    constexpr int operator()(E e) const noexcept
    {
        return static_cast<int>(e);
    }
};

// Extern declaration of the callable instance
extern const ToIntFn ToInt;
