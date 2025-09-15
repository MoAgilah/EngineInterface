#include "InputManager.h"

#include <algorithm>

InputManager::InputManager(const INativeKeyConverter* keyConverter)
    : m_converter(keyConverter)
{
    m_keyStates.fill(false);
    m_keyPressTimestamps.fill(std::chrono::steady_clock::time_point::min());
}

void InputManager::ProcessPlatformKeyPress(void* platformKey) {
    KeyCode key = m_converter->ConvertRaw(platformKey);
    SetKeyPressed(key);
}

void InputManager::ProcessPlatformKeyRelease(void* platformKey) {
    KeyCode key = m_converter->ConvertRaw(platformKey);
    SetKeyReleased(key);
}

bool InputManager::IsAnyKeyPressed() const {
    return std::any_of(m_keyStates.begin(), m_keyStates.end(), [](bool state) { return state; });
}

KeyCode InputManager::GetFirstPressedKey(const std::vector<KeyCode>& keys) const
{
    KeyCode firstKey = KeyCode::Unknown;
    auto earliestTime = std::chrono::steady_clock::time_point::max();

    for (auto key : keys)
    {
        const auto time = m_keyPressTimestamps[static_cast<int>(key)];
        if (time != std::chrono::steady_clock::time_point::min() && time < earliestTime)
        {
            earliestTime = time;
            firstKey = key;
        }
    }

    return firstKey;
}

void InputManager::SetKeyPressed(KeyCode key) {
    if (key == KeyCode::Unknown) return;

    int index = static_cast<int>(key);
    if (!m_keyStates[index])
        m_keyPressTimestamps[index] = std::chrono::steady_clock::now();

    m_keyStates[index] = true;
}

void InputManager::SetKeyReleased(KeyCode key) {
    if (key == KeyCode::Unknown) return;

    int index = static_cast<int>(key);
    m_keyStates[index] = false;
    m_keyPressTimestamps[index] = std::chrono::steady_clock::time_point::min();
}
