#pragma once

#include "FakeDrawable.h"
#include <Engine/Interface/Drawables/ISprite.h>

class FakeSprite : FakeDrawable<FakeSprite>, public ISprite
{
public:
	FakeSprite(const std::string& texId)
	{
		SetTexture(texId);
	}

	void Update(float dt) override {}
	void Render(IRenderer* renderer) override {}

	bool SetTexture(const std::string& texId)
	{
		m_texID = texId;
		return true;
	}

	void SetDirection(bool dir) override {}

	virtual Vector2u GetTextureSize() const override {}
	virtual void SetTextureRect(const IntRect& rect) override {}
};

