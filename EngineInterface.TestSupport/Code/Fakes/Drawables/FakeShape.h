#pragma once

#include <Engine/Interface/Drawables/IShape.h>
#include "FakeDrawable.h"

template<typename TShape>
class FakeShape : public FakeDrawable<TShape>, public IShape
{
public:
	void Update(const Vector2f& pos) {}
	virtual void Render(IRenderer* renderer) {}

	void SetRotation(float rotation) {}

	Colour GetFillColour() { return Colour(); }
	void SetFillColour(const Colour& col) {}

	Colour GetOutlineColour() { return Colour(); }
	void SetOutlineColour(const Colour& col) {}

	float GetOutlineThickness() { return 0.0f; }
	void SetOutlineThickness(float scale) {}
private:

};

class FakeBox : public FakeShape<FakeBox>, public IBoxShape
{
public:
	void Render(IRenderer* renderer) {}

	void Reset(const Vector2f& size) {}

	Vector2f GetSize() { return Vector2f(); }
	void SetSize(const Vector2f& size) {}
};