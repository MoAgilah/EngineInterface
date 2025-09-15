#pragma once

#include <string_view>

class GameManager;

class IGameState
{
public:
    explicit IGameState(GameManager* gameMgr)
        : m_gameMgr(gameMgr)
    {
    }

    virtual ~IGameState() = default;

    virtual std::string_view GetStateName() const = 0;

    virtual void Initialise() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void ProcessInputs() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

protected:

    GameManager* m_gameMgr;
};