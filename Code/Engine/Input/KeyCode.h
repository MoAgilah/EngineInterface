#pragma once

#include <cstdint>

enum class KeyCode : int16_t
{
    // Unknown
    Unknown = -1,

    // Alphabet keys
    A = 0, B, C, D, E, F, G, H, I, J,
    K, L, M, N, O, P, Q, R, S, T,
    U, V, W, X, Y, Z,

    // Number keys (top row)
    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    // Function keys
    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,
    F13, F14, F15,

    // Control keys
    Escape, Enter, Backspace, Tab, Space,
    Pause, Insert, Delete, Home, End,
    PageUp, PageDown,

    // Arrow keys
    Left, Right, Up, Down,

    // Modifier keys
    LControl, LShift, LAlt, LSystem,
    RControl, RShift, RAlt, RSystem,

    // Symbol keys
    Semicolon, Comma, Period, Apostrophe,
    Slash, Backslash, Grave, Equal, Hyphen,
    LBracket, RBracket,

    // Keypad (numpad) keys
    Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
    Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
    Add, Subtract, Multiply, Divide,

    // Application/menu key
    Menu
};

static constexpr unsigned int KeyCount{ static_cast<unsigned int>(KeyCode::Menu) + 1 };