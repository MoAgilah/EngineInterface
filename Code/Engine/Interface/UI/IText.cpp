#include "IText.h"

TextConfig::TextConfig()
	: m_fontName("Standard"), m_charSize(0), m_position(Vector2f()), m_colour(Colour::Black), m_animType(TextAnimType::Static), m_alignment(TextAlignment::None)
{}

TextConfig::TextConfig(const std::string& fontName)
	: m_fontName(fontName), m_charSize(0), m_position(Vector2f()), m_colour(Colour::Black), m_animType(TextAnimType::Static), m_alignment(TextAlignment::None)
{}

TextConfig::TextConfig(const std::string& fontName, unsigned int charSize, const Vector2f& position, TextAnimType textAnimType, Colour colour, TextAlignment alignment)
	: m_fontName(fontName), m_charSize(charSize), m_position(position), m_colour(colour), m_animType(textAnimType), m_alignment(alignment)
{}

TextConfig::TextConfig(const TextConfig& config)
	: m_fontName(config.m_fontName), m_charSize(config.m_charSize), m_position(config.m_position), m_colour(config.m_colour), m_animType(config.m_animType), m_alignment(config.m_alignment)
{}

Vector2f CalculateTextOrigin(const Vector2f& boundsSize, const Vector2f& boundsPos)
{
	return { boundsPos.x + boundsSize.x / 2.f, boundsPos.y + boundsSize.y / 2.f };
}

Vector2f SetTextPosition(TextAlignment alignment, const Vector2f& textPos, const Vector2f& boundsSize, const Vector2f& boundsPos)
{
	switch (alignment)
	{
	case TextAlignment::LeftHand:
		return { textPos.x, textPos.y - boundsSize.y / 2.f };
	case TextAlignment::Center:
		return { textPos.x - boundsSize.x / 2.f - boundsPos.x,
			textPos.y - boundsSize.y / 2.f };
	case TextAlignment::RightHand:
		return { textPos.x - boundsSize.x - boundsPos.x,
			textPos.y - boundsSize.y / 2.f };
		break;
	default:
		CalculateTextOrigin(boundsSize, boundsPos);
		return textPos;
	}
}

IText::IText(const TextConfig& config)
	: m_config(config)
{
}