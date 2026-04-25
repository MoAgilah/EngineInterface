#pragma once

#include <map>

struct ToIntFn
{
	template <typename E>
	constexpr int operator()(E e) const noexcept
	{
		return static_cast<int>(e);
	}
};

extern const ToIntFn ToInt;

class MovementState
{
public:
	void AddVelocity(int ID, float value);
	void AddAcceleration(int ID, float value);
	void AddDeceleration(int ID, float value);

	float GetVelocity(int ID) const;
	void SetCurrentVelLimit(int ID);
	float GetCurrentVelLimit() const { return m_currVelLimit; }

	float GetAcceleration(int ID) const;
	void SetCurrentAccel(int ID);
	float GetCurrentAccel() const { return m_currAccel; }

	float GetDeceleration(int ID) const;
	void SetCurrentDecel(int ID);
	float GetCurrentDecel() const { return m_currDecel; }

private:
	float m_currVelLimit = 0.0f;
	float m_currAccel = 0.0f;
	float m_currDecel = 0.0f;

	std::map<int, float> m_velocities;
	std::map<int, float> m_accelerations;
	std::map<int, float> m_decelerations;
};

class MovementController
{
public:
	~MovementController() = default;

	void AddMovementXState(int ID, const MovementState& state);
	void AddMovementYState(int ID, const MovementState& state);

	void ChangeMovementXState(int ID);
	void ChangeMovementYState(int ID);

	const MovementState& GetCurrentXState() const { return m_currentXState; }
	const MovementState& GetCurrentYState() const { return m_currentYState; }

	void SetCurrentVelLimitForXState(int ID);
	void SetCurrentVelLimitForYState(int ID);

	void SetCurrentAccelForXState(int ID);
	void SetCurrentAccelForYState(int ID);

	void SetCurrentDecelForXState(int ID);
	void SetCurrentDecelForYState(int ID);

private:
	bool m_hasCurrentXState = false;
	bool m_hasCurrentYState = false;

	MovementState m_currentXState;
	MovementState m_currentYState;

	std::map<int, MovementState> m_movementXState;
	std::map<int, MovementState> m_movementYState;
};
