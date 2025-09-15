#pragma once

#include "GameObject.h"
#include "../Engine/Core/Timer.h"

class StaticCollectable : public GameObject
{
public:
	StaticCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos);
	~StaticCollectable() override = default;

	bool GetActive() const final { return !GetCollected() && GameObject::GetActive(); }

	void SetCollected() { m_collected = true; }
	bool GetCollected() const { return m_collected; }

	virtual void Collect(GameObject* obj) = 0;

private:

	virtual void Init(const Vector2f& initPos);

	bool m_collected = false;
};

class DynamicCollectable : public DynamicGameObject
{
public:
	DynamicCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos);
	~DynamicCollectable() override = default;

	bool GetActive() const final { return !GetCollected() && DynamicGameObject::GetActive(); }

	void SetCollected() { m_collected = true; }
	bool GetCollected() const { return m_collected; }

	virtual void Collect(GameObject* obj) = 0;

private:

	virtual void Init(const Vector2f& initPos);

	bool m_collected = false;
};