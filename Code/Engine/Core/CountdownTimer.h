#pragma once

class CountdownTimer
{
public:
	CountdownTimer(float maxTime);
	~CountdownTimer() = default;

	void Update(float deltaTime);

	float GetCurrTime() const { return m_time; }
	void SetCurrTime(float time);

	bool CheckEnd() const { return m_time <= 0.0f; }
	void ForceEnd() { m_time = 0; }

	void Pause() { m_stopped = true; }
	void Resume() { m_stopped = false; }

	void RestartTimer();

	void SetMaxTime(float maxTime);
	float GetMaxTime() const { return m_maxTime; }
private:

	float m_time = 0;
	float m_maxTime;
	bool m_stopped = false;
};