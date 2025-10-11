#include "IScene.h"

#include "../Renderer/ICamera.h"
#include "../../Core/Constants.h"
#include "../../Core/GameManager.h"
#include "../../../Utilities/Utils.h"

void IScene::Update(float deltaTime)
{
	UpdateGUI(deltaTime);

	for (const auto& [_, enemy] : m_enemies)
	{
		CONTINUE_IF_INVALID(enemy);

		if (!enemy->GetActive())
			continue;

		enemy->Update(deltaTime);
	}

	for (const auto& [_, object] : m_objects)
	{
		CONTINUE_IF_INVALID(object);

		if (!object->GetActive())
			continue;

		object->Update(deltaTime);
	}
}

void IScene::Render(IRenderer* renderer)
{
	ENSURE_VALID(m_backgroundSpr);
	m_backgroundSpr->Render(renderer);

	for (const auto& [_, enemy] : m_enemies)
	{
		CONTINUE_IF_INVALID(enemy);

		if (!enemy->GetActive())
			continue;

		enemy->Render(renderer);
	}

	for (const auto& [_, object] : m_objects)
	{
		CONTINUE_IF_INVALID(object);

		if (!object->GetActive())
			continue;

		object->Render(renderer);
	}

	RenderGUI(renderer);
}

void IScene::ResetScene()
{
	for (const auto& key : m_spawnedObjKeys)
		m_objects.erase(key);

	m_spawnedObjKeys.clear();

	for (auto& [_, enemy] : m_enemies)
	{
		CONTINUE_IF_INVALID(enemy);
		enemy->Reset();
	}

	for (auto& [_, object] : m_objects)
	{
		CONTINUE_IF_INVALID(object);
		object->Reset();
	}
}

void IScene::CheckIsInView()
{
	DECL_GET_OR_RETURN(gameMgr, GameManager::Get());
	DECL_GET_OR_RETURN(camera, gameMgr->GetCamera());

	for (auto& [_, enemy] : m_enemies)
	{
		CONTINUE_IF_INVALID(enemy);
		enemy->SetActive(camera->IsInView(enemy->GetVolume()));
	}

	for (auto& [_, object] : m_objects)
	{
		CONTINUE_IF_INVALID(object);
		object->SetActive(camera->IsInView(object->GetVolume()));
	}
}

GameObject* IScene::GetObjectByName(const std::string& name)
{
	auto it = m_objects.find(name);

	if (it != m_objects.end())
		return it->second.get();

	return nullptr;
}

Enemy* IScene::GetEnemyByName(const std::string& name)
{
	auto it = m_enemies.find(name);

	if (it != m_enemies.end())
		return it->second.get();

	return nullptr;
}

void IScene::RenderGUI(IRenderer* renderer)
{
	for (auto spr : m_sprites)
	{
		CONTINUE_IF_INVALID(spr);

		spr->Render(renderer);
	}

	for (auto text : m_texts)
	{
		CONTINUE_IF_INVALID(text);

		text->Render(renderer);
	}
}