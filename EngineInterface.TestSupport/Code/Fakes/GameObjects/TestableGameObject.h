#pragma once

#include <GameObjects/GameObject.h>

class TestableGameObject : public GameObject
{
public:
	using GameObject::GameObject;
	using GameObject::s_objectNum;

	TestableGameObject()
		: GameObject() {}

	TestableGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, bool active = false, bool dir = true, Vector2f pos = Vector2f())
		:GameObject(drawable, volume)
	{
		SetInitialActive(active);
		SetInitialDirection(dir);
		SetInitialPosition(pos);

		SetActive(GetInitialActive());
		SetDirection(GetInitialDirection());
		SetPosition(GetInitialPosition());

		m_volume->Update(GetPosition());
	}

	void SetVolumeForTesting(std::shared_ptr<IBoundingVolume> volume)
	{
		m_volume = std::move(volume);
	}

	void Update(float deltatime) override {}

	void OnCollisionEnter(IGameObject* obj) override {}

	void OnCollisionStay(IGameObject* obj) override {}

	void OnCollisionExit(IGameObject* obj) override {}

	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) override {}

};

class TestableDynamicGameObject : public DynamicGameObject
{
public:
	using DynamicGameObject::DynamicGameObject;

	TestableDynamicGameObject()
		: DynamicGameObject() {}

	TestableDynamicGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, bool active = false, bool dir = true, Vector2f pos = Vector2f())
		: DynamicGameObject(drawable, volume)
	{
		SetInitialActive(active);
		SetInitialDirection(dir);
		SetInitialPosition(pos);

		SetActive(GetInitialActive());
		SetDirection(GetInitialDirection());
		SetPosition(GetInitialPosition());

		m_volume->Update(GetPosition());
	}

	void SetVolumeForTesting(std::shared_ptr<IBoundingVolume> volume)
	{
		m_volume = std::move(volume);
	}

	void Update(float deltatime) override {}

	void OnCollisionEnter(IGameObject* obj) override {}

	void OnCollisionStay(IGameObject* obj) override {}

	void OnCollisionExit(IGameObject* obj) override {}

	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) override {}

};