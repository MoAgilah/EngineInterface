#pragma once

#include <Engine/Interface/Renderer/ICamera.h>
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Collisions/BoundingCapsule.h>
#include <Engine/Collisions/BoundingCircle.h>
#include "../Drawables/FakeShape.h"

class FakeCamera : public ICamera
{
public:
	FakeCamera()
		: ICamera(std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16)))
	{ }
	void Update() override {}
	void Reset(IRenderer* renderer) override {}
	void RenderDebug(IRenderer* renderer) override {}

	bool IsInView(IBoundingVolume* volume) override
	{
		isInViewCallCount++;
		return isInViewResult;
	}

	bool CheckVerticalBounds(IBoundingVolume* volume) override { return checkVerticalBounds; }

public:

	bool isInViewResult = true;
	bool checkVerticalBounds = false;
	int isInViewCallCount = 0;
};

