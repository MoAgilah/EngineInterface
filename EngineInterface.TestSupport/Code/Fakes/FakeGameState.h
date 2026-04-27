#pragma once

#include <Engine/Core/GameManager.h>
#include <Engine/Interface/Scene/IGameState.h>
#include <string>

class FakeGameState : public IGameState
{
public:
	FakeGameState(const std::string& name, GameManager* gameMgr);

    std::string_view GetStateName() const override { return m_name; }

    void Initialise() override;
    void Pause() override;
    void Resume() override;
    void ProcessInputs() override;
    void Update(float deltaTime) override;
    void Render() override;

public:

	std::string m_name;

    bool initialisedCalled = false;
    bool pauseCalled = false;
    int  pauseCallCount = 0;
    bool resumeCalled = false;
    int  resumeCallCount = 0;
    bool processInputCalled = false;
    bool updateCalled = false;
    bool renderCalled = false;
};
