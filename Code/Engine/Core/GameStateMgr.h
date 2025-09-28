#pragma once

#include <string>
#include <vector>

template <typename T>
class GameStateMgr
{
public:
	~GameStateMgr();

	std::string_view GetStateName();

	void ChangeState(T* state);
	void PushState(T* state);
	void PopState();
	void ClearStates();

	void Pause();
	void Resume();

	void ProcessInputs();
	void Update(float deltaTime);
	void Render();

private:

	std::vector<T*> m_vGameStates;
};
