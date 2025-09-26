#pragma once

#include <string>
#include <map>

class Physics
{
public:
	void AddVelocity(const std::string& name, float value);
	float GetVelocity(const std::string& name);

	void AddAcceleration(const std::string& name, float value);
	float GetAcceleration(const std::string& name);

	void AddDeceleration(const std::string& name, float value);
	float GetDeceleration(const std::string& name);

private:

	std::map<std::string, float> m_velocities;
	std::map<std::string, float> m_accelerations;
	std::map<std::string, float> m_decelartions;
};

class MovementController
{
public:
	~MovementController() = default;

	void AddPhysicsState(const std::string& name, const Physics& physics);

	void ChangePhysicsState(const std::string& name);

	std::pair<std::string, Physics>& GetCurrentState() { return m_currentState; }

private:

	std::pair<std::string, Physics> m_currentState;
	std::map<std::string, Physics> m_physicsState;
};