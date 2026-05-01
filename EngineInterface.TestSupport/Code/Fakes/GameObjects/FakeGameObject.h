#pragma once

#include <GameObjects/GameObject.h>
#include <Utilities/Guards.h>

class FakeGameObject : public GameObject
{
public:
	FakeGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	{
		m_drawable = std::move(drawable);
		m_volume = std::move(volume);

		if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
			throw std::invalid_argument("FakeGameObject requires a valid drawable");

		if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
			throw std::invalid_argument("FakeGameObject requires a valid volume");

		SetTypeIndex(typeid(FakeGameObject));
	}

	void SetsIntersects(bool value) { intersects = value; }

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
	{
		m_drawable = std::move(drawable);
		m_volume = std::move(volume);

		if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
			throw std::invalid_argument("FakeGameObject requires a valid drawable");

		if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
			throw std::invalid_argument("FakeGameObject requires a valid volume");

		SetTypeIndex(typeid(DynamicFakeGameObject));
	}

	void SetsIntersects(bool value) { intersects = value; }

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

