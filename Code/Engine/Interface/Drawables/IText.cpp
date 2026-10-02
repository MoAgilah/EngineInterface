#include "IText.h"

TextConfig::TextConfig()
	: m_fontName("Standard"), m_charSize(0), m_position(Vector2f()), m_colour(Colour::Black), m_alignment(TextAlignment::None)
{}

TextConfig::TextConfig(const std::string& fontName)
	: m_fontName(fontName), m_charSize(0), m_position(Vector2f()), m_colour(Colour::Black), m_alignment(TextAlignment::None)
{}

TextConfig::TextConfig(const std::string& fontName, unsigned int charSize, const Vector2f& position, Colour colour, TextAlignment alignment)
	: m_fontName(fontName), m_charSize(charSize), m_position(position), m_colour(colour), m_alignment(alignment)
{}

TextConfig::TextConfig(const TextConfig& config)
	: m_fontName(config.m_fontName), m_charSize(config.m_charSize), m_position(config.m_position), m_colour(config.m_colour), m_alignment(config.m_alignment)
{}

IText::IText(const TextConfig& config)
	: m_config(config)
{
}