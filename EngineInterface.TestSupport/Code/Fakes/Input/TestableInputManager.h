#pragma once

#include <Engine/Input/InputManager.h>

class TestableInputManager : public InputManager
{
public:
	explicit TestableInputManager(std::shared_ptr<IKeyConverter> converter)
		: InputManager(converter)
	{}

	bool IsValidKeyForTesting(KeyCode key) const { return IsValidKey(key); }

	void SetKeyPressedForTesting(KeyCode key) { SetKeyPressed(key); }
	void SetKeyReleasedForTesting(KeyCode key) { SetKeyReleased(key); }

};