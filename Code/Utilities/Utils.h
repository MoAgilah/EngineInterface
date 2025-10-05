#pragma once

#include <iostream>

// =========================
// Pointer validation macros
// =========================

// Use this to check a getter-style expression that returns a pointer.
// Example:
//   GET_OR_RETURN(renderer, m_gameMgr->GetRenderer());
//   renderer->Draw();
#define GET_OR_RETURN(var, expr)                             \
    auto var = (expr);                                        \
    if (!(var)) {                                             \
        std::cerr << "[ERROR] Null pointer in " << __func__   \
                  << " at " << __FILE__ << ":" << __LINE__    \
                  << " (" #expr " returned null)\n";          \
        return;                                               \
    }

// Use this to validate an incoming pointer argument at function entry.
// Example:
//   void Render(Renderer* renderer) {
//       ENSURE_VALID(renderer);
//       renderer->Draw();
//   }
#define ENSURE_VALID(ptr)                                     \
    if (!(ptr)) {                                             \
        std::cerr << "[ERROR] Invalid pointer '" #ptr         \
                  << "' in " << __func__                      \
                  << " at " << __FILE__ << ":" << __LINE__    \
                  << "\n";                                    \
        return;                                               \
    }

#define ENSURE_VALID_RET(ptr, retval)                          \
    if (!(ptr)) {                                              \
        std::cerr << "[ERROR] Invalid pointer '" #ptr          \
                  << "' in " << __func__                       \
                  << " at " << __FILE__ << ":" << __LINE__     \
                  << "\n";                                     \
        return (retval);                                       \
    }

// Skip to the next iteration if the pointer is invalid
#define CONTINUE_IF_INVALID(ptr)                              \
    if (!(ptr)) {                                             \
        std::cerr << "[WARN] Invalid pointer '" #ptr          \
                  << "' in " << __func__                      \
                  << " at " << __FILE__ << ":" << __LINE__    \
                  << " -> continuing loop\n";                 \
        continue;                                             \
    }

// Get pointer and continue loop if result is invalid
#define GET_OR_CONTINUE(var, expr)                            \
    auto var = (expr);                                        \
    if (!(var)) {                                             \
        std::cerr << "[WARN] Null pointer in " << __func__    \
                  << " at " << __FILE__ << ":" << __LINE__    \
                  << " (" #expr " returned null) -> continuing loop\n"; \
        continue;                                             \
    }

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
