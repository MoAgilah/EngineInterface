#pragma once

#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render(IRenderer* renderer) = 0;
};