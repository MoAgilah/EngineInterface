#include "FakeGameState.h"

FakeGameState::FakeGameState(const std::string& name, GameManager* gameMgr)
	: IGameState(gameMgr), m_name(name)
{}

void FakeGameState::Initialise()
{
	initialisedCalled = true;
}

void FakeGameState::Pause()
{
	pauseCallCount++;
	pauseCalled = true;
}

void FakeGameState::Resume()
{
	resumeCallCount++;
	resumeCalled = true;
}

void FakeGameState::ProcessInputs()
{
	processInputCalled = true;
}

void FakeGameState::Update(float deltaTime)
{
	updateCalled = true;
}

void FakeGameState::Render()
{
	renderCalled = true;
}
