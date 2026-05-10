#pragma once

#include <Engine/Interface/Scene/IScene.h>
#include <Utilities/Guards.h>
#include "../GameObjects/FakeGameObject.h"
#include "../GameObjects/FakeEnemy.h"
#include "../Drawables/FakeSprite.h"
#include "../UI/FakeText.h"

class FakeScene : public IScene
{
public:
	using IScene::m_objects;
	using IScene::m_enemies;
	using IScene::m_sprites;
	using IScene::m_texts;
	using IScene::m_spawnedObjKeys;

	using IScene::EmplaceEnemyOrThrow;
	using IScene::EmplaceObjectOrThrow;
	using IScene::EmplaceGUISpriteOrThrow;
	using IScene::EmplaceGUITextOrThrow;

	void CheckIsInView() override
	{
		checkIsInViewIsCalled = true;
	}

	void SpawnGameObjectAt(const std::string& id, std::shared_ptr<GameObject> obj, const Vector2f& pos) override
	{
		if (!CheckNotNull(obj.get(), "Invalid Pointer 'obj'"))
			return;

		obj->SetPosition(pos);

		if (m_objects.find(id) != m_objects.end())
			throw std::runtime_error("Duplicate object key");

		auto [it, inserted] = m_objects.emplace(id, std::move(obj));

		if (!inserted)
		{
			throw std::runtime_error("Duplicate object key");
		}

		m_spawnedObjKeys.push_back(it->first);
	}

protected:

	bool AddEnemies() override
	{
		if (!addEnemiesResult)
			return false;

		EmplaceEnemyOrThrow<FakeEnemy>("Enemy1", "Enmy1", false);
		EmplaceEnemyOrThrow<FakeEnemy>("Enemy2", "Enmy2", true);

		return true;
	}

	bool AddGUI() override
	{
		if (!addGUIResult)
			return false;

		EmplaceGUISpriteOrThrow<FakeSprite>("Sprite1", "Spr1");

		EmplaceGUISpriteOrThrow<FakeSprite>("Sprite2", "Spr2");

		EmplaceGUITextOrThrow<FakeText>(
			"Text1",
			TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
			"Txt1"
		);

		EmplaceGUITextOrThrow<FakeText>(
			"Text2",
			TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
			"Txt2"
		);

		return true;
	}

	bool AddObjects() override
	{
		if (!addObjectsResult)
			return false;

		EmplaceObjectOrThrow<FakeDynamicGameObject>("DynamicGameObject1", std::make_shared<FakeSprite>("DynObj1"), std::make_shared<BoundingBox<FakeBox>>(), true);
		EmplaceObjectOrThrow<FakeDynamicGameObject>("DynamicGameObject2", std::make_shared<FakeSprite>("DynObj2"), std::make_shared<BoundingBox<FakeBox>>(), false);

		return true;
	}

	bool AddForeGroundObjects() override
	{
		if (!addForeGroundObjectsResult)
			return false;

		EmplaceObjectOrThrow<FakeGameObject>("GameObject1", std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), false);
		EmplaceObjectOrThrow<FakeGameObject>("GameObject2", std::make_shared<FakeSprite>("Obj2"), std::make_shared<BoundingBox<FakeBox>>(), true);

		return true;
	}

	void UpdateGUI(float deltaTime) override
	{
		updateGUICalled = true;
		lastGUIDeltaTime = deltaTime;

		for (auto& [id, spr] : m_sprites)
		{
			if (!CheckNotNull(spr.get(),
				std::format("Invalid Pointer 'spr' with key {}", id)))
				continue;

			spr->Update(deltaTime);
		}

		for (auto& [id, txt] : m_texts)
		{
			if (!CheckNotNull(txt.get(),
				std::format("Invalid Pointer 'txt' with key {}", id)))
				continue;

			txt->Update(deltaTime);
		}
	}

	void RenderGUI(IRenderer* renderer) override
	{
		renderGUICalled = true;
		IScene::RenderGUI(renderer);
	}

public:

	bool addEnemiesResult = true;
	bool addGUIResult = true;
	bool addObjectsResult = true;
	bool addForeGroundObjectsResult = true;

	bool checkIsInViewIsCalled = false;
	bool updateGUICalled = false;
	bool renderGUICalled = false;

	float lastGUIDeltaTime = 0.0f;

	std::vector<std::string>* renderLog = nullptr;
};