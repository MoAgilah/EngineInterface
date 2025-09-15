#pragma once

#include "IWindow.h"
#include "../../../Utilities/Vector.h"
#include <memory>

class IRenderable;

class IRenderer
{
public:
	virtual ~IRenderer() = default;

	virtual void Initialise(const Vector2f& screenDims, const std::string& title) = 0;
	virtual void PollWindowEvents() = 0;
	virtual void Clear() = 0;
	virtual void Draw(IRenderable* object) =  0;
	virtual void Present() = 0;

	INativeWindow* GetWindow() { return m_window.get(); }

protected:

	std::shared_ptr<INativeWindow> m_window;
};