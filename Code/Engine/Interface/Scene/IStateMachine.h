#pragma once

#include "IGameObject.h"
#include <string>

class IStateMachine
{
public:
    explicit IStateMachine(std::shared_ptr<IGameObject> gameObj)
        : m_gameObj(gameObj)
    {}

    virtual ~IStateMachine() = default;

    virtual std::string_view GetStateName() const = 0;

    virtual void Initialise() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void ProcessInputs() = 0;
    virtual void Update(float deltaTime) = 0;

protected:

    std::shared_ptr<IGameObject> m_gameObj;
};