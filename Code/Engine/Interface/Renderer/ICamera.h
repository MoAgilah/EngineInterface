#pragma once

#include "IRenderer.h"
#include "../Collisions/IBoundingVolume.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../Utilities/Guards.h"
#include <memory>
#include <stdexcept>

class ICamera
{
public:
    ICamera(std::unique_ptr<IBoundingBox> viewBox)
        : m_viewBox(std::move(viewBox)), m_toFollow(nullptr)
    {
        if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        {
            throw std::invalid_argument("ICamera requires a valid BoundingBox Volume");
        }
    }
    virtual ~ICamera() = default;

    void SetObjectToFollow(std::shared_ptr<GameObject> obj)
    {
        m_toFollow = std::move(obj);
    }

    virtual void Update() = 0;
    virtual void Reset(IRenderer* renderer) = 0;

    virtual void RenderDebug(IRenderer* renderer)
    {
        if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
            return;

        m_viewBox->Render(renderer);
    }

    virtual bool IsInView(IBoundingVolume* volume)
    {
        if (!CheckNotNull(volume, "Invalid Pointer 'volume'"))
            return false;

        return m_viewBox->Intersects(volume);
    }

    virtual bool CheckVerticalBounds(IBoundingVolume* volume)
    {
        if (!CheckNotNull(volume, "Invalid Pointer 'volume'"))
            return false;

        const float cameraBottom = m_viewBox->GetWorldBounds().Max().y;

        return volume->GetWorldBounds().Max().y > cameraBottom;
    }

protected:

    std::shared_ptr<GameObject> m_toFollow;
    std::unique_ptr<IBoundingBox> m_viewBox;
};
