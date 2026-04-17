#include "IScene.h"

#include "../Collisions/ITile.h"
#include "../Renderer/ICamera.h"
#include "../../Core/Constants.h"
#include "../../Core/GameManager.h"
#include "../../../Utilities/Guards.h"
#include <exception>

bool IScene::Initialise()
{
	if (!AddEnemies())
		throw std::runtime_error("IScene::Initialise - AddEnemies() failed");

	if (!AddGUI())
		throw std::runtime_error("IScene::Initialise - AddGUI() failed");

	if (!AddObjects())
		throw std::runtime_error("IScene::Initialise - AddObjects() failed");

	if (!AddForeGroundObjects())
		throw std::runtime_error("IScene::Initialise - AddForeGroundObjects() failed");

	return true;
}

void IScene::Update(float deltaTime)
{
	UpdateGUI(deltaTime);

	for (auto& [id, enemy] : m_enemies)
	{
		if (!CheckNotNull(enemy.get(),
			std::format("Invalid Pointer 'enemy' with key {}", id)))
			continue;

		if (!enemy->GetActive())
			continue;

		enemy->Update(deltaTime);
	}

	for (auto& [id, object] : m_objects)
	{
		if (!CheckNotNull(object.get(),
			std::format("Invalid Pointer 'object' with key {}", id)))
			continue;

		if (!object->GetActive())
			continue;

		object->Update(deltaTime);
	}
}

void IScene::Render(IRenderer* renderer)
{
	if (!CheckNotNull(m_backgroundSpr.get(), "Invalid Pointer 'm_backgroundSpr' from GameManager::Get()"))
		return;

	m_backgroundSpr->Render(renderer);

	for (auto& [id, enemy] : m_enemies)
	{
		if (!CheckNotNull(enemy.get(),
			std::format("Invalid Pointer 'enemy' with key {}", id)))
			continue;

		if (!enemy->GetActive())
			continue;

		enemy->Render(renderer);
	}

	for (auto& [id, object] : m_objects)
	{
		if (!CheckNotNull(object.get(),
			std::format("Invalid Pointer 'object' with key {}", id)))
			continue;

		if (!object->GetActive())
			continue;

		object->Render(renderer);
	}

	if (GameConstants::DRender)
	{
		auto* gameMgr = GameManager::Get();
		if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
			return;

		auto* colMgr = gameMgr->GetCollisionMgr();
		if (!CheckNotNull(colMgr, "Invalid Pointer 'colMgr' from gameMgr->GetCollisionMgr()"))
			return;

		colMgr->Render(renderer);

		gameMgr->GetCamera()->RenderDebug(renderer);
	}

	RenderGUI(renderer);
}

void IScene::ResetScene()
{
	for (const auto& key : m_spawnedObjKeys)
		m_objects.erase(key);

	m_spawnedObjKeys.clear();

	for (auto& [id, enemy] : m_enemies)
	{
		if (!CheckNotNull(enemy.get(),
			std::format("Invalid Pointer 'enemy' with key {}", id)))
			continue;

		enemy->Reset();
	}

	for (auto& [id, object] : m_objects)
	{
		if (!CheckNotNull(object.get(),
			std::format("Invalid Pointer 'object' with key {}", id)))
			continue;

		object->Reset();
	}
}

void IScene::CheckIsInView()
{
	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		return;

	auto* camera = gameMgr->GetCamera();
	if (!CheckNotNull(camera, "Invalid Pointer 'colMgr' from gameMgr->GetCamera()"))
		return;

	for (auto& [id, enemy] : m_enemies)
	{
		if (!CheckNotNull(enemy.get(),
			std::format("Invalid Pointer 'enemy' with key {}", id)))
			continue;

		enemy->SetActive(camera->IsInView(enemy->GetVolume()));
	}

	for (auto& [id, object] : m_objects)
	{
		if (!CheckNotNull(object.get(),
			std::format("Invalid Pointer 'object' with key {}", id)))
			continue;

		object->SetActive(camera->IsInView(object->GetVolume()));
	}

	auto* colMgr = gameMgr->GetCollisionMgr();
	if (!CheckNotNull(colMgr, "Invalid Pointer 'colMgr' from gameMgr->GetCollisionMgr()"))
		return;

	const auto& grid = colMgr->GetGrid();

	for (size_t i = 0; i < grid.size(); ++i)
	{
		auto* tile = grid[i];

		if (!CheckNotNull(tile,
			std::format("Invalid Pointer 'tile' at index {}", i)))
			continue;

		tile->SetActive(camera->IsInView(tile->GetBoundingBox()));
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

ISprite* IScene::GetGUISpriteByName(const std::string& name)
{
	auto it = m_sprites.find(name);

	if (it != m_sprites.end())
		return it->second.get();

	return nullptr;
}

IText* IScene::GetGUITextByName(const std::string& name)
{
	auto it = m_texts.find(name);

	if (it != m_texts.end())
		return it->second.get();

	return nullptr;
}

void IScene::RenderGUI(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

	for (auto& [id, spr] : m_sprites)
	{
		if (!CheckNotNull(spr.get(),
			std::format("Invalid Pointer 'spr' with key {}", id)))
			continue;

		spr->Render(renderer);
	}

	for (auto& [id, text] : m_texts)
	{
		if (!CheckNotNull(text.get(),
			std::format("Invalid Pointer 'text' with key {}", id)))
			continue;

		text->Render(renderer);
	}
}