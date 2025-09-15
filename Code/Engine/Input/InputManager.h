#pragma once
#include "KeyCode.h"
#include "../Interface/Input/IKeyConverter.h"
#include <array>
#include <chrono>

class InputManager {
public:
    explicit InputManager(const INativeKeyConverter* keyConverter);

    void ProcessPlatformKeyPress(void* platformKey);
    void ProcessPlatformKeyRelease(void* platformKey);

    bool GetKeyState(int key) { return m_keyStates[key]; }

    bool IsAnyKeyPressed() const;

    std::chrono::steady_clock::time_point GetKeyPressTimestamp(KeyCode key) const
    {
        return m_keyPressTimestamps[static_cast<int>(key)];
    }

    KeyCode GetFirstPressedKey(const std::vector<KeyCode>& keys) const;

private:
    void SetKeyPressed(KeyCode key);
    void SetKeyReleased(KeyCode key);

    const INativeKeyConverter* m_converter;

    std::array<bool, KeyCount> m_keyStates{};
    std::array<std::chrono::steady_clock::time_point, KeyCount> m_keyPressTimestamps{};
};
