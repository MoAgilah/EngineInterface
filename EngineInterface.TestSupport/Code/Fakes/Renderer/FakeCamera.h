#pragma once

#include <Engine/Interface/Renderer/ICamera.h>

class FakeCamera : ICamera
{
public:

	void Update() override {}
	void Reset(IRenderer* renderer) override {}
	void RenderDebug(IRenderer* renderer) override {}

	bool IsInView(IBoundingVolume* volume) override
	{
		isInViewCallCount++;
		return isInViewResult;
	}

	bool CheckVerticalBounds(IBoundingVolume* volume) override {}

public:

	bool isInViewResult = true;
	int isInViewCallCount = 0;
};

