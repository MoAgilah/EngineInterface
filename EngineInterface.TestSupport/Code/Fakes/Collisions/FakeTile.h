#pragma once

#include <Engine/Interface/Collisions/ITile.h>

class FakeTile : public ITile
{
public:
	FakeTile(int gX, int gY)
	: ITile(gX, gY, nullptr, nullptr, nullptr)
	{}

	void Render(IRenderer* renderer) override {}

	void ResolveCollision(IDynamicGameObject* obj, float tFirst, float tLast) override {}

	void SetPosition(const Vector2f& pos) override {}

	void SetFillColour(Colour col) override {}
	void SetOutlineColour(Colour col) override {}

protected:

	bool ResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast) override {}
	bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override {}
	bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override {}
	void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) override {}
};