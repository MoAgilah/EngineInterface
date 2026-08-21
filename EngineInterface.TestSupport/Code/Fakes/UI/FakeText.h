#pragma once

#include <Engine/Interface/Scene/IGameState.h>
#include <string>
#include <string_view>

class FakeText : public IText
{
public:
	FakeText(const TextConfig& config, const std::string& id)
		: IText(config)
	{
		renderId = id;
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

	Colour GetOutlineColour() override { return m_config.m_colour; }
	void SetOutlineColour(const Colour& colour) override { m_config.m_colour = colour; }

	Colour GetFillColour() override { return Colour(); }
	void SetFillColour(const Colour& colour) override {}

	float GetOutlineThickness() override { return 3.f; }
	void SetOutlineThickness(float thickness) override {}

protected:

	bool Init() override { return true; }

public:

	std::string m_text;

	int renderCount = 0;
	int updateCount = 0;

	float lastDeltaTime = 0.0f;

	std::vector<std::string>* renderLog = nullptr;
	std::string renderId = "text";
};

