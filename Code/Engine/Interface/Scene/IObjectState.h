#pragma once

#include "../../../GameObjects/GameObject.h"
#include "../../../Utilities/Guards.h"
#include <string>

class IObjectState
{
public:
    explicit IObjectState(DynamicGameObject* gameObj)
        : m_gameObj(gameObj), m_drawable(nullptr)
    {
        if (!CheckNotNull(m_gameObj, "Invalid Pointer 'm_gameObj'"))
            throw std::invalid_argument("IObjectState requires a valid game object");

        m_drawable = m_gameObj->GetDrawable();
        if (!CheckNotNull(m_drawable, "Invalid Pointer 'm_drawable' from m_gameObj->GetDrawable()"))
            throw std::runtime_error("IObjectState requires a valid drawable");
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