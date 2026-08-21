#pragma once

#include "GameObject.h"
#include "../Engine/Interface/Scene/ICollectable.h"
#include "../Engine/Core/CountdownTimer.h"

class StaticCollectable : public GameObject, public virtual ICollectable
{
public:
	StaticCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos);
	~StaticCollectable() override = default;

	void OnCollisionEnter(IGameObject* obj) override;
	void OnCollisionStay(IGameObject* obj) override;
	void OnCollisionExit(IGameObject* obj) override;
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) override;

	bool GetActive() const final { return IsCollectableActive(GameObject::GetActive()); }

private:

	virtual void Init(const Vector2f& initPos);
};

class DynamicCollectable : public DynamicGameObject, public virtual ICollectable
{
public:
	DynamicCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos);
	~DynamicCollectable() override = default;

	void OnCollisionEnter(IGameObject* obj) override;
	void OnCollisionStay(IGameObject* obj) override;
	void OnCollisionExit(IGameObject* obj) override;
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) override;

	bool GetActive() const final { return IsCollectableActive(DynamicGameObject::GetActive()); }

private:

	virtual void Init(const Vector2f& initPos);
};