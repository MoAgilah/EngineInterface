#pragma once

#include "../Resources/IShader.h"
#include "../../../Utilities/Guards.h"

class IShaderEffect
{
public:
    IShaderEffect(IShader* shader)
        : m_shader(shader)
    {
        if (!CheckNotNull(m_shader, "Invalid Pointer 'm_shader'"))
            throw std::invalid_argument("IShaderEffect requires a valid shader");
    }

    virtual ~IShaderEffect() = default;

    virtual void Update(float deltaTime) = 0;

    IShader* GetShader() const { return m_shader; }

protected:

    IShader* m_shader = nullptr;
};