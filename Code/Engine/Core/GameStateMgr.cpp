#include "GameStateMgr.h"

#include "../Interface/Scene/IGameState.h"
#include "../Interface/Scene/IObjectState.h"
#include "../Core/Constants.h"
#include <format>
#include <iostream>

template<typename T>
GameStateMgr<T>::~GameStateMgr()
{
	ClearStates();
}

template<typename T>
std::string_view GameStateMgr<T>::GetStateName()
{
	if (!m_vGameStates.empty())
		return m_vGameStates.back()->GetStateName();

	return std::string_view();
}

template<typename T>
void GameStateMgr<T>::ChangeState(T* state)
{
	if (!m_vGameStates.empty())
		m_vGameStates.pop_back();

	m_vGameStates.push_back(state);
	m_vGameStates.back()->Initialise();

	if (GameConstants::DRender)
		std::cout << std::format("Changed too {} state\n", m_vGameStates.back()->GetStateName());
}

template<typename T>
void GameStateMgr<T>::PushState(T* state)
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->Pause();

	m_vGameStates.push_back(state);
	m_vGameStates.back()->Initialise();

	if (GameConstants::DRender)
		std::cout << std::format("Pushed {} state\n", m_vGameStates.back()->GetStateName());
}

template<typename T>
void GameStateMgr<T>::PopState()
{
	if (!m_vGameStates.empty())
	{
		if (GameConstants::DRender)
			std::cout << std::format("Popped {} state\n", m_vGameStates.back()->GetStateName());
		m_vGameStates.pop_back();
	}

	if (!m_vGameStates.empty())
		m_vGameStates.back()->Resume();
}

template<typename T>
void GameStateMgr<T>::ClearStates()
{
	while (!m_vGameStates.empty())
		m_vGameStates.pop_back();
}

template<typename T>
void GameStateMgr<T>::Pause()
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->Pause();
}

template<typename T>
void GameStateMgr<T>::Resume()
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->Resume();
}

template<typename T>
void GameStateMgr<T>::ProcessInputs()
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->ProcessInputs();
}

template<typename T>
void GameStateMgr<T>::Update(float deltaTime)
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->Update(deltaTime);
}

template<typename T>
void GameStateMgr<T>::Render()
{
	if (!m_vGameStates.empty())
		m_vGameStates.back()->Render();
}

void GameStateMgr<IObjectState>::Render()
{
}

template class GameStateMgr<IGameState>;
template class GameStateMgr<IObjectState>;