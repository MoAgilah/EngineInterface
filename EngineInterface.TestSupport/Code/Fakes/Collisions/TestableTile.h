#pragma once

#include "FakeBoundingBox.h"
#include <Engine/Interface/Collisions/ITile.h>

class TestableTile : public ITile
{
public:
	TestableTile(int gX, int gY, std::shared_ptr<IBoundingBox> aabb, std::shared_ptr<ITriangleShape> slope)
		: ITile(gX, gY, std::move(aabb), nullptr, std::move(slope))
	{}

	void Render(IRenderer* renderer) override {}

	void ResolveCollision(IDynamicGameObject* obj, float tFirst, float tLast) override
	{
		resolveCollisionCalled = true;
		resolvedObject = obj;
		resolvedTFirst = tFirst;
		resolvedTLast = tLast;
	}

	void SetFillColour(Colour col) override {}
	void SetOutlineColour(Colour col) override {}

	Vector2f Test_GetSeparationVector(IDynamicGameObject* obj)
	{
		return GetSeparationVector(obj);
	}

	void Test_ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast)
	{
		ResolveObjectToBoxTop(obj, tFirst, tLast);
	}

	void Test_ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast)
	{
		ResolveObjectToBoxBottom(obj, tFirst, tLast);
	}

	void Test_ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast)
	{
		ResolveObjectToBoxHorizontally(obj, tFirst, tLast);
	}

protected:

	bool ResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast) override { return false; }
	bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override { return false; }
	bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override { return false; }
	void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) override {}

public:

	bool resolveCollisionCalled = false;

	IDynamicGameObject* resolvedObject = nullptr;
	float resolvedTFirst = 0.f;
	float resolvedTLast = 0.f;
};
