#include "MovementController.h"

void MovementState::AddVelocity(int ID, float value)
{
	m_velocities.insert({ ID,value });
}

void MovementState::AddAcceleration(int ID, float value)
{
	m_accelerations.insert({ ID,value });
}

void MovementState::AddDeceleration(int ID, float value)
{
	m_decelartions.insert({ ID,value });
}

float MovementState::GetVelocity(int ID)
{
	auto it = m_velocities.find(ID);
	if (it != m_velocities.end())
		return it->second;

	return 0.0f;
}

void MovementState::SetCurrentVelLimit(int ID)
{
	m_currVelLimit = GetVelocity(ID);
}

float MovementState::GetAcceleration(int ID)
{
	auto it = m_accelerations.find(ID);
	if (it != m_accelerations.end())
		return it->second;

	return 0.0f;
}

void MovementState::SetCurrentAccel(int ID)
{
	m_currAccel = GetAcceleration(ID);
}

float MovementState::GetDeceleration(int ID)
{
	auto it = m_decelartions.find(ID);
	if (it != m_decelartions.end())
		return it->second;

	return 0.0f;
}

void MovementState::SetCurrentDecel(int ID)
{
	m_currDecel = GetDeceleration(ID);
}

void MovementController::AddMovementXState(int ID, const MovementState& state)
{
	m_movementXState.insert({ ID, state });
}

void MovementController::AddMovementYState(int ID, const MovementState& state)
{
	m_movementYState.insert({ ID, state });
}

void MovementController::ChangeMovementXState(int ID)
{
	auto it = m_movementXState.find(ID);
	if (it != m_movementXState.end())
		m_currentXState = it->second;
}

void MovementController::ChangeMovementYState(int ID)
{
	auto it = m_movementYState.find(ID);
	if (it != m_movementYState.end())
		m_currentYState = it->second;
}
