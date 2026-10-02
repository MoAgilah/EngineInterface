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
{}

ICountdownText::ICountdownText(float countdownInterval, int startFrom, const std::string& countDownMessage)
    : m_countdownInterval(countdownInterval), m_timer(m_countdownInterval)
{
    ThrowIfFalse(
        countdownInterval > 0.f,
        "Flash duration must be greater than zero"
    );

    SetMaxCount(startFrom);
    SetCountDownMsg(countDownMessage);
}

void ICountdownText::Update(float deltaTime)
{
    if (m_countEnded)
        return;

    m_timer.Update(deltaTime);

    if (!m_timer.CheckEnd())
        return;

    --m_count;

    if (m_count <= 0)
    {
        m_count = 0;
        m_countEnded = true;
        return;
    }

    m_timer.RestartTimer();
}

void ICountdownText::SetMaxCount(int startFrom)
{
    ThrowIfFalse(
        startFrom > 0,
        "Countdown start value must be greater than zero."
    );

    m_count = m_maxCount = startFrom;
    m_countEnded = false;
}
