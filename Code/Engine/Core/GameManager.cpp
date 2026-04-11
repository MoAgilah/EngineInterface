#include "GameManager.h"

#include "Constants.h"
#include "../Interface/Collisions/ITile.h"
#include "../../Utilities/Utils.h"
#include "../../Utilities/LogFormatter.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
	: m_gameTimer(GameConstants::CountdownDuration)
{
	auto filename = logger::FormatFilenameTimestamp() + ".log";

	m_logger.Start(filename);

	m_instance = this;
}

GameManager::~GameManager()
{
	m_logger.Stop();

	if (m_instance)
		m_instance = nullptr;
}

void GameManager::CheckInView()
{
	ENSURE_VALID(m_collisionManager);
	ENSURE_VALID(m_camera);

	for (auto& tile : m_collisionManager->GetGrid())
	{
		CONTINUE_IF_INVALID(tile);
		tile->SetActive(m_camera->IsInView(tile->GetBoundingBox()));
	}

	ENSURE_VALID(m_scene);
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