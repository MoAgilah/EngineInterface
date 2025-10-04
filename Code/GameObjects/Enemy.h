#pragma once

#include "GameObject.h"
#include "../Engine/Core/Timer.h"

class Player;

class Enemy : public DynamicGameObject
{
public:
	Enemy(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, int maxLives = 1);
	~Enemy() override = default;

	bool GetActive() const final { return GetIsAlive() && IGameObject::GetActive(); }

	void Update(float deltaTime) override;

	void OnCollisionEnter(IGameObject* obj);
	void OnCollisionStay(IGameObject* obj);
	void OnCollisionExit(IGameObject* obj);
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition);

	void Reset() override;

	void SetDirection(bool dir) override;

	bool GetAirbourne() const { return m_airbourne; }
	void SetAirbourne(bool air) { m_airbourne = air; }

	bool GetIsAlive() const { return m_isAlive; }
	bool HasLifes() const { return m_numLives > 0; }
	virtual void DecrementLife();
	virtual void Die() = 0;

	bool GetInvulnerabe() const { return m_invulnerable; }
	void SetInvulnerability(bool val) { m_invulnerable = val; }

	Timer* GetAirTimer() { return &m_airTimer; }
	void SetAirTime(float time);
	void SetTimeLeftActive(float time);

	void SetSpeedX(float spd) { m_speed.x = spd; }
	void SetSpeedY(float spd) { m_speed.y = spd; }

	float GetSpeedX() { return m_speed.x; }
	float GetSpeedY() { return m_speed.y; }

private:

	virtual void Animate(float deltaTime) = 0;

	int m_maxLives;
	int m_numLives = 1;
	bool m_isAlive = true;
	bool m_airbourne = false;
	bool m_invulnerable = false;
	bool m_resetAllowed = false;
	Vector2f m_speed;
	Timer m_airTimer;
	Timer m_resetTimer;
	Timer m_activationTimer;
};
