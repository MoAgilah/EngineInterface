#include "Timer.h"

Timer::Timer(float maxTime)
	: m_maxTime(maxTime)
{
	RestartTimer();
}

void Timer::Update(float deltaTime)
{
	if (!m_stopped)
		m_time -= deltaTime;
}

void Timer::RestartTimer()
{
	m_time = m_maxTime;
}