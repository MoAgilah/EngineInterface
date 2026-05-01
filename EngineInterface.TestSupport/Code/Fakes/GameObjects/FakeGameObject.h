#pragma once

#include <GameObjects/GameObject.h>

class FakeGameObject : public GameObject
{
public:
	FakeGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
		: GameObject(std::move(drawable), std::move(volume))
	{}

	void SetsIntersects(bool intersects) { intersects = intersects; }

	void Update(float deltaTime) override {}
	void Render(IRenderer* renderer) override {}
	bool Intersects(IGameObject* obj)  override { return intersects; }
	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) { return intersects; }
	void OnCollisionEnter(IGameObject* obj)  override {}
	void OnCollisionStay(IGameObject* obj)  override {}
	void OnCollisionExit(IGameObject* obj)  override {}
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition)  override {}
	void Reset()  override {}

public:

	bool intersects = false;
};

class DynamicFakeGameObject : public DynamicGameObject
{
public:
	DynamicFakeGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
		: DynamicGameObject(std::move(drawable), std::move(volume))
	{}

	void SetsIntersects(bool intersects) { intersects = intersects; }

	void Update(float deltaTime) override {}
	void Render(IRenderer* renderer) override {}
	bool Intersects(IGameObject* obj)  override { return intersects; }
	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) { return intersects; }
	void OnCollisionEnter(IGameObject* obj)  override {}
	void OnCollisionStay(IGameObject* obj)  override {}
	void OnCollisionExit(IGameObject* obj)  override {}
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition)  override {}
	void Reset()  override {}

public:

	bool intersects = false;
};

