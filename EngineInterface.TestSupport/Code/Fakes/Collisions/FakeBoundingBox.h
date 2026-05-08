#pragma once

#include <Engine/Collisions/BoundingBox.h>
#include "../Drawables/FakeShape.h"

class FakeBoundingBox : public BoundingBox<FakeBox>
{
public:
    FakeBoundingBox()
        : IBoundingVolume(VolumeType::Box)
        , BoundingBox<FakeBox>()
    {
    }

    FakeBoundingBox(const Vector2f& size, const Vector2f& pos)
        : IBoundingVolume(VolumeType::Box)
        , BoundingBox<FakeBox>(size, pos)
    {
    }

    bool IntersectsMoving(
        IBoundingVolume* v,
        const Vector2f& va,
        const Vector2f& vb,
        float& tFirst,
        float& tLast) override
    {
        if (!v)
            return false;

        intersectsMovingCalled = true;

        tFirst = 0.25f;
        tLast = 0.75f;

        return true;
    }

public:

    bool intersectsMovingCalled = false;
};