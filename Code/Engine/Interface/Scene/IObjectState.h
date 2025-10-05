#pragma once

#include "../../../GameObjects/GameObject.h"
#include "../../../Utilities/Utils.h"
#include <string>

class IObjectState
{
public:
    explicit IObjectState(DynamicGameObject* gameObj)
        : m_gameObj(gameObj), m_drawable(nullptr)
    {
        ENSURE_VALID(m_gameObj);
        GET_OR_RETURN(m_drawable, m_gameObj->GetDrawable());
    }

    virtual ~IObjectState() = default;

    virtual std::string_view GetStateName() const = 0;

    virtual void Initialise() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void ProcessInputs() = 0;
    virtual void Update(float deltaTime) = 0;

protected:

    virtual void UpdateAnimation() = 0;

    IDrawable* m_drawable;
    DynamicGameObject* m_gameObj;
};