#pragma once

#include "../Scene/ITransforms.h"
#include "../Renderer/IRenderer.h"
#include "../../../Utilities/Rect.h"

class ISprite : public IMoveable
{
public:
	virtual ~ISprite() = default;

	virtual void Update(float dt) = 0;
	virtual void Render(IRenderer* renderer) = 0;

	std::string_view GetTexID() const { return m_texID; }

	virtual void SetTexture(const std::string& texId) = 0;

	virtual Vector2i GetTextureSize() const = 0;
	virtual void SetTextureRect(const IntRect& rect) = 0;

protected:

	std::string m_texID;
};