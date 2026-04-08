#pragma once

#include <string_view>
#include <Engine/Interface/Scene/IGameState.h>

class GameManager;

class FakeGameState : public IGameState
{
public:
    explicit FakeGameState(GameManager* gm, std::string_view name = "Fake")
        : IGameState(gm)
        , m_name(name)
    {
    }

    std::string_view GetStateName() const override
    {
        return m_name;
    }

    void Initialise() override
    {
        initialiseCalled = true;
    }

    void Pause() override
    {
        pauseCalled = true;
    }

    void Resume() override
    {
        resumeCalled = true;
    }

    void ProcessInputs() override
    {
        processInputsCalled = true;
    }

    void Update(float deltaTime) override
    {
        updateCalled = true;
        lastDelta = deltaTime;
    }

    void Render() override
    {
        renderCalled = true;
    }

    bool initialiseCalled = false;
    bool pauseCalled = false;
    bool resumeCalled = false;
    bool processInputsCalled = false;
    bool updateCalled = false;
    bool renderCalled = false;
    float lastDelta = 0.0f;

private:
    std::string_view m_name;
};