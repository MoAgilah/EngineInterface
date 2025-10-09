#pragma once

#include "../Renderer/IRenderer.h"
#include "../../../Utilities/Colour.h"
#include "../../../Utilities/Vector.h"
#include <string>
#include <functional>

enum class TextAnimType
{
	Unassigned, Static, Flashing, Countdown, Custom
};

enum class TextAlignment
{
	None, LeftHand, Center, RightHand
};

struct TextConfig
{
	TextConfig();

	TextConfig(const std::string& fontName);

	TextConfig(const std::string& fontName, unsigned int charSize, const Vector2f& position, TextAnimType textAnimType, Colour colour = Colour::Black, TextAlignment alignment = TextAlignment::Center);

	TextConfig(const TextConfig& config);

	std::string m_fontName;
	unsigned int m_charSize;
	Vector2f m_position;
	Colour m_colour;
	TextAnimType m_animType;
	TextAlignment m_alignment;
};

Vector2f CalculateTextOrigin(const Vector2f& boundsSize, const Vector2f& boundsPos);

Vector2f SetTextPosition(TextAlignment alignment, const Vector2f& textPos, const Vector2f& boundsSize, const Vector2f& boundsPos);

class IText
{
public:
	IText(){}
	IText(const TextConfig& config);
	virtual ~IText() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render(IRenderer* renderer) = 0;

	virtual void SetText(const std::string& text) = 0;

	virtual unsigned int GetCharSize() = 0;
	virtual void SetCharSize(unsigned int charSize) = 0;

	virtual Colour GetOutlineColour() = 0;
	virtual void SetOutlineColour(const Colour& colour) = 0;

	virtual Colour GetFillColour() = 0;
	virtual void SetFillColour(const Colour& colour) = 0;

	virtual float GetOutlineThickness() = 0;
	virtual void SetOutlineThickness(float thickness) = 0;

	bool IsAnimated() const { return m_config.m_animType > TextAnimType::Static; }
	const Colour& GetDefaultColour() const { return m_config.m_colour; }

protected:

	virtual bool Init() = 0;

	TextConfig m_config;
};

using UpdateFunc = std::function<void(float)>;
using RenderFunc = std::function<void(IRenderer* renderer)>;

struct CustomTextConfig
{
	CustomTextConfig(const TextConfig& config, UpdateFunc updateFunc, RenderFunc renderFunc, const std::string& shaderName = "");

	TextConfig m_config;
	UpdateFunc m_updateFunc;
	RenderFunc m_renderFunc;
	std::string m_shaderName;
};