#pragma once

#include "../Scene/IUpdatable.h"
#include "../Effects/IEffect.h"
#include "../Resources/IShader.h"
#include "../../../Utilities/Guards.h"

class IShaderEffect : public IEffect, public IUpdatable
{
public:
    IShaderEffect(IShader* shader)
        : m_shader(shader)
    {
        if (!CheckNotNull(m_shader, "Invalid Pointer 'm_shader'"))
            throw std::invalid_argument("IShaderEffect requires a valid shader");
    }

    virtual ~IShaderEffect() = default;

    IShader* GetShader() const { return m_shader; }

protected:

    IShader* m_shader = nullptr;
};