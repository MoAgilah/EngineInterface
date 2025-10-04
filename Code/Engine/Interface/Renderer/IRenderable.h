#pragma once

#include "IRenderer.h"
#include "../Resources/IShader.h"

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render(IRenderer* renderer) = 0;
	virtual void Render(IRenderer* renderer, IShader* shader) = 0;
};