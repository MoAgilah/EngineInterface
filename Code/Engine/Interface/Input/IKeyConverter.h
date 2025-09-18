#pragma once

#include "../../Input/KeyCode.h"

class IKeyConverter
{
public:
	virtual ~IKeyConverter() = default;
	// platformCode = platform/native key or scancode; your SFML backend will translate it.
	virtual KeyCode ConvertFromPlatform(int platformCode) const = 0;
};
