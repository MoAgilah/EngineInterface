#include "MovementController.h"

void Physics::AddVelocity(const std::string& name, float value)
{
	m_velocities.insert({ name,value });
}

float Physics::GetVelocity(const std::string& name)
{
	auto it = m_velocities.find(name);
	if (it != m_velocities.end())
		return it->second;

	return 0.0f;
}

void Physics::AddAcceleration(const std::string& name, float value)
{
	m_accelerations.insert({ name,value });
}

float Physics::GetAcceleration(const std::string& name)
{
	auto it = m_accelerations.find(name);
	if (it != m_accelerations.end())
		return it->second;

	return 0.0f;
}

void Physics::AddDeceleration(const std::string& name, float value)
{
	m_decelartions.insert({ name,value });
}

float Physics::GetDeceleration(const std::string& name)
{
	auto it = m_decelartions.find(name);
	if (it != m_decelartions.end())
		return it->second;

	return 0.0f;
}

void MovementController::AddPhysicsState(const std::string& name, const Physics& physics)
{
	m_physicsState.insert({ name, physics });
}

void MovementController::ChangePhysicsState(const std::string& name)
{
	auto it = m_physicsState.find(name);
	if (it != m_physicsState.end())
		m_currentState = *it;
}