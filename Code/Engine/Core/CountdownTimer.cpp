#include "CountdownTimer.h"

#include <algorithm>

CountdownTimer::CountdownTimer(float maxTime)
	: m_maxTime(std::max(0.0f, maxTime))
{
	RestartTimer();
}

void CountdownTimer::Update(float deltaTime)
{
	if (deltaTime < 0.0f)
		return;

	if (m_stopped || m_time <= 0.0f)
		return;

	m_time -= deltaTime;

	if (m_time < 0.0f)
		m_time = 0.0f;
}

void CountdownTimer::SetCurrTime(float time)
{
	m_time = std::clamp(time, 0.0f, m_maxTime);
}

void CountdownTimer::SetMaxTime(float maxTime)
{
	m_maxTime = std::max(0.0f, maxTime);
	m_time = std::clamp(m_time, 0.0f, m_maxTime);
}

void CountdownTimer::RestartTimer()
{
	m_time = m_maxTime;
	m_stopped = false;
}