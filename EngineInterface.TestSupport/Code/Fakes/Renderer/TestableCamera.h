#pragma once

#include <Engine/Interface/Renderer/ICamera.h>
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Collisions/BoundingCapsule.h>
#include <Engine/Collisions/BoundingCircle.h>
#include "../Drawables/FakeShape.h"

class TestableCamera : public ICamera
{
public:
	TestableCamera(std::unique_ptr<IBoundingBox> viewBox)
		: ICamera(std::move(viewBox))
	{
	}

	IBoundingBox* GetViewBoxForTesting() { return m_viewBox.get(); }

	void Update() {}
	void Reset(IRenderer* renderer) {}
};