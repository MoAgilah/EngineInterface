#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(float maxTime)
	: m_maxTime(maxTime)
{
	RestartTimer();
}

void CountdownTimer::Update(float deltaTime)
{
	if (m_stopped || m_time <= 0.0f)
		return;

	m_time -= deltaTime;

	if (m_time < 0.0f)
		m_time = 0.0f;
}

void CountdownTimer::RestartTimer()
{
	m_time = m_maxTime;
	m_stopped = false;
}