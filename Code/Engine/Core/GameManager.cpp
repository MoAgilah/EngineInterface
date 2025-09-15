#include "GameManager.h"

#include "Constants.h"
#include "../Interface/Collisions/ITile.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
	: m_timer(300.f)
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
	for (auto& tile : m_collisionManager->GetGrid())
		tile->SetActive(m_camera->IsInView(tile->GetBoundingBox()));

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