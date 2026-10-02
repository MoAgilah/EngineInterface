#pragma once

#include "../../Core/CountdownTimer.h"
#include "../Effects/IShaderEffect.h"
#include "../Renderer/IRenderer.h"
#include "../../../Utilities/Colour.h"
#include "../../../Utilities/Vector2.h"
#include <functional>
#include <string>

enum class TextAlignment
{
	None, LeftHand, Center, RightHand
};

struct TextConfig
{
	TextConfig();

	TextConfig(const std::string& fontName);

	TextConfig(const std::string& fontName, unsigned int charSize, const Vector2f& position, Colour colour = Colour::Black, TextAlignment alignment = TextAlignment::Center);

	TextConfig(const TextConfig& config);

	std::string m_fontName;
	unsigned int m_charSize;
	Vector2f m_position;
	Colour m_colour;
	TextAlignment m_alignment;
};

class IText
{
public:
	IText(){}
	IText(const TextConfig& config);
	virtual ~IText() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render(IRenderer* renderer) = 0;

	virtual void SetText(const std::string& text) = 0;

	void SetEffect(std::unique_ptr<IShaderEffect> shaderEffect)
	{
		m_shaderEffect = std::move(shaderEffect);
	}

	IShaderEffect* GetEffect() const
	{
		return m_shaderEffect.get();
	}

	virtual unsigned int GetCharSize() = 0;
	virtual void SetCharSize(unsigned int charSize) = 0;

	virtual Colour GetOutlineColour() = 0;
	virtual void SetOutlineColour(const Colour& colour) = 0;

	virtual Colour GetFillColour() = 0;
	virtual void SetFillColour(const Colour& colour) = 0;

	virtual float GetOutlineThickness() = 0;
	virtual void SetOutlineThickness(float thickness) = 0;

	const Colour& GetDefaultColour() const { return m_config.m_colour; }

protected:

	virtual bool Init() = 0;

	void UpdateEffect(float deltaTime)
	{
		if (m_shaderEffect)
			m_shaderEffect->Update(deltaTime);
	}

	TextConfig m_config;
	std::unique_ptr<IShaderEffect> m_shaderEffect;
};

class ICountdownText
{
public:
	ICountdownText(float countdownInterval, int startFrom, const std::string& countDownMessage);
	virtual ~ICountdownText() = default;

	void Update(float deltaTime);

	int GetCount() const { return m_count; }

	void SetMaxCount(int startFrom);
	bool CountHasEnded() const { return m_countEnded; }

	std::string_view GetCountDownMsg() const { return m_countdownMsg; }
	void SetCountDownMsg(const std::string& msg) { m_countdownMsg = msg; }

protected:

	int m_count = 0;
	int m_maxCount = 0;
	bool m_countEnded = false;
	float m_countdownInterval;
	std::string m_countdownMsg;
	CountdownTimer m_timer;
};