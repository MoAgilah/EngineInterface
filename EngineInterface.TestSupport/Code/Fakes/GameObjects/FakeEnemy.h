#pragma once

#include <Engine/Collisions/BoundingBox.h>
#include <GameObjects/Enemy.h>
#include <Utilities/Guards.h>
#include "../Drawables/FakeShape.h"

class FakeEnemy : public Enemy
{
public:
	FakeEnemy(const std::string& id,
		bool active,
		int maxLives = 1)
		: Enemy(maxLives)
	{
		this->m_drawable = std::make_shared<FakeSprite>(id);
		this->m_volume = std::make_shared<BoundingBox<FakeBox>>();

		if (!CheckNotNull(this->m_drawable.get(), "Invalid Pointer 'm_drawable'"))
			throw std::invalid_argument("FakeObject requires a valid drawable");

		if (!CheckNotNull(this->m_volume.get(), "Invalid Pointer 'm_volume'"))
			throw std::invalid_argument("FakeObject requires a valid volume");

		this->SetTypeIndex(typeid(FakeEnemy));

		SetActive(active);

		this->renderId = id;
	}

	void Update(float deltaTime) override
	{
		updateCount++;
		lastDeltaTime = deltaTime;
	}

	void Render(IRenderer* renderer) override
	{
		renderCount++;

		if (renderLog)
			renderLog->push_back(renderId);
	}

	void Reset() override
	{
		resetCount++;
		Enemy::Reset();
	}

	void Die() override
	{
		dieCalled = true;
	}

	void Animate(float deltaTime) override
	{
		animateCount++;
		lastAnimateDeltaTime = deltaTime;
	}

public:

	int updateCount = 0;
	int renderCount = 0;
	int resetCount = 0;
	int animateCount = 0;

	float lastDeltaTime = 0.0f;
	float lastAnimateDeltaTime = 0.0f;

	bool dieCalled = false;

	std::vector<std::string>* renderLog = nullptr;
	std::string renderId = "enemy";
};