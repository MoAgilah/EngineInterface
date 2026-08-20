#pragma once

#include "../Drawables/FakeSprite.h"
#include <GameObjects/Enemy.h>
#include <Utilities/Guards.h>

class TestableEnemy : public Enemy
{
public:
	TestableEnemy(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, bool active = true, bool dir = true, Vector2f pos = Vector2f(), int maxLives = 1)
		: Enemy(drawable, volume, maxLives)
	{
		SetInitialActive(active);
		SetInitialDirection(dir);
		SetInitialPosition(pos);

		SetActive(GetInitialActive());
		SetDirection(GetInitialDirection());
		SetPosition(GetInitialPosition());

		if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
			throw std::invalid_argument("DynamicGameObject requires a valid volume");

		m_volume->Update(GetPosition());
	}

	~TestableEnemy() override = default;

	int GetNumLivesForTesting() const { return m_numLives; }
	int GetMaxLivesForTesting() const { return m_maxLives; }

	bool GetResetAllowedForTesting() const { return m_resetAllowed; }
	bool SetResetAllowedForTesting(bool res) { return m_resetAllowed = res; }

	CountdownTimer* GetResetTimerForTesting() { return &m_resetTimer; }
	CountdownTimer* GetActivationTimerForTesting() { return &m_activationTimer; }

	void Die() override
	{
		dieCount++;
	}

protected:

	void Animate(float deltaTime) override
	{
		animateCount++;
		lastAnimateDeltaTime = deltaTime;
	}

public:

	int dieCount = 0;
	int animateCount = 0;
	float lastAnimateDeltaTime = 0.0f;
};