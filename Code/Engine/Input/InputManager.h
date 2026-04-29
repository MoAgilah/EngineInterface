#pragma once

#include "KeyCode.h"
#include "../Interface/Input/IKeyConverter.h"
#include <array>
#include <chrono>
#include <memory>
#include <vector>

class InputManager
{
public:
    explicit InputManager(std::shared_ptr<IKeyConverter> converter);

    void ProcessPlatformKeyPress(int platformKey);
    void ProcessPlatformKeyRelease(int platformKey);

    bool GetKeyState(int key) { return m_keyStates[key]; }

    bool IsAnyKeyPressed() const;

    std::chrono::steady_clock::time_point GetKeyPressTimestamp(KeyCode key) const
    {
        return m_keyPressTimestamps[static_cast<int>(key)];
    }

    KeyCode GetFirstPressedKey(const std::vector<KeyCode>& keys) const;

private:

    bool IsValidKey(KeyCode key) const;

    void SetKeyPressed(KeyCode key);
    void SetKeyReleased(KeyCode key);

    std::shared_ptr<IKeyConverter> m_converter;

    std::array<bool, KeyCount> m_keyStates{};
    std::array<std::chrono::steady_clock::time_point, KeyCount> m_keyPressTimestamps{};
};
