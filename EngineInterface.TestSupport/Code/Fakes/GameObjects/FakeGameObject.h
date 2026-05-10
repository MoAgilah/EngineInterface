#pragma once

#include "../Drawables/FakeSprite.h"
#include <GameObjects/GameObject.h>
#include <Utilities/Guards.h>

template <typename Base>
class FakeObjectBase : public Base
{
public:
	FakeObjectBase(std::shared_ptr<IDrawable> drawable,
		std::shared_ptr<IBoundingVolume> volume)
		: Base()
	{
		this->m_drawable = std::move(drawable);
		this->m_volume = std::move(volume);

		if (!CheckNotNull(this->m_drawable.get(), "Invalid Pointer 'm_drawable'"))
			throw std::invalid_argument("FakeObject requires a valid drawable");

		if (!CheckNotNull(this->m_volume.get(), "Invalid Pointer 'm_volume'"))
			throw std::invalid_argument("FakeObject requires a valid volume");
	}

	void SetIntersects(bool value)
	{
		intersects = value;
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

	bool Intersects(IGameObject* obj) override
	{
		return intersects;
	}

	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) override
	{
		return intersects;
	}

	void OnCollisionEnter(IGameObject* obj) override {}
	void OnCollisionStay(IGameObject* obj) override {}
	void OnCollisionExit(IGameObject* obj) override {}

	void ResolveCollisions(float time,
		const Vector2f& separationVector,
		float relativeHitPosition) override {
	}

	void Reset() override
	{
		resetCount++;
	}

public:
	bool intersects = false;

	int updateCount = 0;
	int renderCount = 0;
	int resetCount = 0;

	float lastDeltaTime = 0.0f;

	std::vector<std::string>* renderLog = nullptr;
	std::string renderId;
};

class FakeGameObject : public FakeObjectBase<GameObject>
{
public:
	FakeGameObject(std::shared_ptr<IDrawable> drawable,
		std::shared_ptr<IBoundingVolume> volume,
		bool active = false)
		: FakeObjectBase<GameObject>(std::move(drawable), std::move(volume))
	{
		if (auto fakeSprite =
			std::dynamic_pointer_cast<FakeSprite>(m_drawable))
		{
			this->renderId = fakeSprite->GetTexID();
		}
		else
		{
			this->renderId = "gameObject";
		}

		this->SetTypeIndex(typeid(FakeGameObject));

		this->SetActive(active);
	}
};

class FakeDynamicGameObject : public FakeObjectBase<DynamicGameObject>
{
public:
	FakeDynamicGameObject(std::shared_ptr<IDrawable> drawable,
		std::shared_ptr<IBoundingVolume> volume,
		bool active = false)
		: FakeObjectBase<DynamicGameObject>(std::move(drawable), std::move(volume))
	{
		if (auto fakeSprite =
			std::dynamic_pointer_cast<FakeSprite>(m_drawable))
		{
			this->renderId = fakeSprite->GetTexID();
		}
		else
		{
			this->renderId = "dynamicGameObject";
		}

		this->SetTypeIndex(typeid(FakeDynamicGameObject));

		this->SetActive(active);
	}
};

