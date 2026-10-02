#pragma once

#include <Engine/Interface/Resources/IShader.h>
#include <string>

class FakeShader : public IShader
{
public:
	FakeShader() = default;

	bool LoadFromFile(const std::string& filepath) override
	{
		return true;
	}

	void SetUniform(
		const std::string& name,
		float value) override
	{
		storedName = name;
		storedValue = value;
	}

public:

	std::string storedName = "";
	float storedValue = 0.f;
};