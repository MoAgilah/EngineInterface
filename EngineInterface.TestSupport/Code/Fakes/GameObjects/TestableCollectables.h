#pragma once

#include <GameObjects/Collectables.h>

class TestableStaticCollectable : public StaticCollectable
{
public:
    using StaticCollectable::StaticCollectable;

    void Collect(IGameObject* obj) override
    {
        SetCollected();
        collectedObject = obj;
    }

    void Update(float deltaTime) override {}

    IGameObject* collectedObject = nullptr;

    void InitCollectableForTesting(const Vector2f& initPos)
    {
        InitCollectable(this, initPos);
    }

    void SetObjectAsNull()
    {
        m_drawable = nullptr;
    }

    void SetVolumeAsNull()
    {
        m_volume = nullptr;
    }
};

class TestableDynamicCollectable : public DynamicCollectable
{
public:
    using DynamicCollectable::DynamicCollectable;

    void Collect(IGameObject* obj) override
    {
        SetCollected();
        collectedObject = obj;
    }

    void Update(float deltaTime) override {}

    IGameObject* collectedObject = nullptr;
};