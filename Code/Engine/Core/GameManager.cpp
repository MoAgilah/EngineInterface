#include "GameManager.h"

#include "Constants.h"
#include "../Interface/Collisions/ITile.h"
#include "../../Utilities/Guards.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
	: m_gameTimer(GameConstants::CountdownDuration)
{
	m_instance = this;
}

GameManager::~GameManager()
{
	if (m_instance)
		m_instance = nullptr;
}

void GameManager::CheckInView()
{
	if (!CheckNotNull(m_collisionManager.get(), "Invalid Pointer 'm_collisionManager'"))
		return;

	if (!CheckNotNull(m_camera.get(), "Invalid Pointer 'm_camera'"))
		return;

	for (auto& tile : m_collisionManager->GetGrid())
	{
		if (!CheckNotNull(tile, "Invalid Pointer 'tile'"))
			continue;

		tile->SetActive(m_camera->IsInView(tile->GetBoundingBox()));
	}

	if (!CheckNotNull(m_scene.get(), "Invalid Pointer 'm_scene'"))
		return;

	m_scene->CheckIsInView();
}

void GameManager::Update(float deltaTime)
{
	m_stateManager.Update(deltaTime);
}

void GameManager::Render()
{
	m_stateManager.Render();
}