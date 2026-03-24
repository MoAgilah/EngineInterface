#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(float maxTime)
	: m_maxTime(maxTime)
{
	RestartTimer();
}

void CountdownTimer::Update(float deltaTime)
{
	if (!m_stopped)
		m_time -= deltaTime;
}

void CountdownTimer::RestartTimer()
{
	m_time = m_maxTime;
}