#pragma once

#include "IRenderer.h"
#include "../Collisions/IBoundingVolume.h"
#include "../../../GameObjects/GameObject.h"
#include <memory>

class ICamera
{
public:
    virtual ~ICamera() = default;

    void SetObjectToFollow(std::shared_ptr<GameObject> obj)
    {
        m_toFollow = std::move(obj);
    }

    virtual void Update() = 0;
    virtual void Reset(IRenderer* renderer) = 0;
    virtual void RenderDebug(IRenderer* renderer) = 0;

    virtual bool IsInView(IBoundingVolume* volume) = 0;
    virtual bool CheckVerticalBounds(IBoundingVolume* volume) = 0;

protected:

    std::shared_ptr<GameObject> m_toFollow;
};
