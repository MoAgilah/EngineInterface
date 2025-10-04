#pragma once

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
