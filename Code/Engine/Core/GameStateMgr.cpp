#include "GameStateMgr.h"

#include "../Core/Constants.h"
#include "../Interface/Scene/IGameState.h"
#include "../Interface/Scene/IObjectState.h"
#include "../../Utilities/Utils.h"
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
	{
		if (auto* s = m_vGameStates.back())
			return s->GetStateName();
	}

	return std::string_view();
}

template<typename T>
void GameStateMgr<T>::ChangeState(T* state)
{
	ENSURE_VALID(state);

	if (!m_vGameStates.empty())
		m_vGameStates.pop_back();

	m_vGameStates.push_back(state);

	if (auto* s = m_vGameStates.back())
	{
		s->Initialise();

		if (GameConstants::DRender)
			std::cout << std::format("Changed too {} state\n", s->GetStateName());
	}
}

template<typename T>
void GameStateMgr<T>::PushState(T* state)
{
	ENSURE_VALID(state);

	T* s;

	if (!m_vGameStates.empty())
	{
		if (s = m_vGameStates.back())
			m_vGameStates.back()->Pause();
	}

	m_vGameStates.push_back(state);
	if (s = m_vGameStates.back())
	{
		s->Initialise();

		if (GameConstants::DRender)
			std::cout << std::format("Pushed {} state\n", s->GetStateName());
	}
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
	{
		if (auto* s = m_vGameStates.back())
			s->Resume();
	}
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
	{
		if (auto* s = m_vGameStates.back())
			s->Pause();
	}
}

template<typename T>
void GameStateMgr<T>::Resume()
{
	if (!m_vGameStates.empty())
	{
		if (auto* s = m_vGameStates.back())
			s->Resume();
	}
}

template<typename T>
void GameStateMgr<T>::ProcessInputs()
{
	if (!m_vGameStates.empty())
	{
		if (auto* s = m_vGameStates.back())
			s->ProcessInputs();
	}
}

template<typename T>
void GameStateMgr<T>::Update(float deltaTime)
{
	if (!m_vGameStates.empty())
	{
		if (auto* s = m_vGameStates.back())
			s->Update(deltaTime);
	}
}

template<typename T>
void GameStateMgr<T>::Render()
{
	if (!m_vGameStates.empty())
	{
		if (auto* s = m_vGameStates.back())
			s->Render();
	}
}

void GameStateMgr<IObjectState>::Render()
{
}

template class GameStateMgr<IGameState>;
template class GameStateMgr<IObjectState>;