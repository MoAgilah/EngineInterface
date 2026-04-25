#include "MovementController.h"

const ToIntFn ToInt{};

void MovementState::AddVelocity(int ID, float value)
{
	m_velocities.insert({ ID, value });
}

void MovementState::AddAcceleration(int ID, float value)
{
	m_accelerations.insert({ ID, value });
}

void MovementState::AddDeceleration(int ID, float value)
{
	m_decelerations.insert({ ID, value });
}

float MovementState::GetVelocity(int ID) const
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

float MovementState::GetAcceleration(int ID) const
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

float MovementState::GetDeceleration(int ID) const
{
	auto it = m_decelerations.find(ID);
	if (it != m_decelerations.end())
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
	if (it == m_movementXState.end())
		return;

	m_currentXState = it->second;
	m_hasCurrentXState = true;
}

void MovementController::ChangeMovementYState(int ID)
{
	auto it = m_movementYState.find(ID);
	if (it == m_movementYState.end())
		return;

	m_currentYState = it->second;
	m_hasCurrentYState = true;
}

void MovementController::SetCurrentVelLimitForXState(int ID)
{
	if (!m_hasCurrentXState)
		return;

	m_currentXState.SetCurrentVelLimit(ID);
}

void MovementController::SetCurrentVelLimitForYState(int ID)
{
	if (!m_hasCurrentYState)
		return;

	m_currentYState.SetCurrentVelLimit(ID);
}

void MovementController::SetCurrentAccelForXState(int ID)
{
	if (!m_hasCurrentXState)
		return;

	m_currentXState.SetCurrentAccel(ID);
}

void MovementController::SetCurrentAccelForYState(int ID)
{
	if (!m_hasCurrentYState)
		return;

	m_currentYState.SetCurrentAccel(ID);
}

void MovementController::SetCurrentDecelForXState(int ID)
{
	if (!m_hasCurrentXState)
		return;

	m_currentXState.SetCurrentDecel(ID);
}

void MovementController::SetCurrentDecelForYState(int ID)
{
	if (!m_hasCurrentYState)
		return;

	m_currentYState.SetCurrentDecel(ID);
}
