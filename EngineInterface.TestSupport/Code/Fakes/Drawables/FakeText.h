#pragma once

#include <Engine/Interface/Drawables/IText.h>

#include <string>
#include <vector>

class FakeText : public IText
{
public:
	FakeText(const TextConfig& config, const std::string& id)
		: IText(config)
	{
		renderId = id;
		fillColour = config.m_colour;
	}

	void Update(float deltaTime) override
	{
		updateCount++;
		lastDeltaTime = deltaTime;
	}

	void Render(IRenderer* renderer) override
	{
		renderCount++;

		if (renderLog)
			renderLog->push_back(renderId);
	}

	void SetText(const std::string& text) override { m_text = text; }

	unsigned int GetCharSize() override { return m_config.m_charSize; }
	void SetCharSize(unsigned int charSize) override { m_config.m_charSize = charSize; }

	const Colour& GetOutlineColour() override { return outlineColour; }
	void SetOutlineColour(const Colour& colour) override { outlineColour = colour; }

	const Colour& GetFillColour() override { return fillColour;  }
	void SetFillColour(const Colour& colour) override { fillColour = colour; }

	float GetOutlineThickness() override { return 3.f; }
	void SetOutlineThickness(float thickness) override {}

protected:

	bool Init() override { return true; }

public:

	std::string m_text;

	int renderCount = 0;
	int updateCount = 0;

	float lastDeltaTime = 0.0f;

	Colour fillColour;
	Colour outlineColour;

	std::vector<std::string>* renderLog = nullptr;
	std::string renderId = "text";
};

