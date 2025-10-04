#pragma once

#include <string>
#include <map>

class MovementState
{
public:
	void AddVelocity(int ID, float value);
	void AddAcceleration(int ID, float value);
	void AddDeceleration(int ID, float value);

	float GetVelocity(int ID);
	void SetCurrentVelLimit(int ID);
	float GetCurrentVelLimit() { return m_currVelLimit; }

	float GetAcceleration(int ID);
	void SetCurrentAccel(int ID);
	float GetCurrentAccel() { return m_currAccel; }

	float GetDeceleration(int ID);
	void SetCurrentDecel(int ID);
	float GetCurrentDecel() { return m_currDecel; }

private:

	float m_currVelLimit = 0;
	float m_currAccel = 0;
	float m_currDecel = 0;

	std::map<int, float> m_velocities;
	std::map<int, float> m_accelerations;
	std::map<int, float> m_decelartions;
};

class MovementController
{
public:
	~MovementController() = default;

	void AddMovementXState(int ID, const MovementState& physics);
	void AddMovementYState(int ID, const MovementState& physics);

	void ChangeMovementXState(int ID);
	void ChangeMovementYState(int ID);

	MovementState& GetCurrentXState() { return m_currentXState; }
	MovementState& GetCurrentYState() { return m_currentYState; }

private:

	MovementState m_currentXState;
	MovementState m_currentYState;
	std::map<int, MovementState> m_movementXState;
	std::map<int, MovementState> m_movementYState;
};
