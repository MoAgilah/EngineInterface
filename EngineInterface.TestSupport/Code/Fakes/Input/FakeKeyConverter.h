#pragma once

#include <Engine/Interface/Input/IKeyConverter.h>

class FakeKeyConverter final : public IKeyConverter
{
public:
	KeyCode ConvertFromPlatform(int platformKey) const override
	{
		return static_cast<KeyCode>(platformKey);
	}
};