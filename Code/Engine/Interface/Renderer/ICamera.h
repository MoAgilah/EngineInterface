#pragma once

#include "IRenderer.h"
#include "../Collisions/IBoundingVolume.h"

class ICamera
{
public:
    virtual ~ICamera() = default;

    virtual void Update() = 0;
    virtual void Reset(IRenderer* renderer) = 0;
    virtual void RenderDebug(IRenderer* renderer) = 0;

    virtual bool IsInView(IBoundingVolume* volume) = 0;
    virtual bool CheckVerticalBounds(IBoundingVolume* volume) = 0;
};
