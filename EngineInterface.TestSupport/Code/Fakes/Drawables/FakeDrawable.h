#pragma once

#include <Engine/Interface/Drawables/IDrawable.h>

template <typename T>
class FakeDrawable: public IDrawable, public CompoundDrawableHolder<T>
{
public:
    virtual ~FakeDrawable() = default;

    void Render(IRenderer* renderer) {}
    void Render(IRenderer* renderer, IShader* shader) {}

    void SetPosition(const Vector2f& pos) {}

    virtual void OffsetPosition(const Vector2f& delta) {}

    Vector2f GetPosition() override { return Vector2f(); }

    void SetScale(const Vector2f& scl) override {}

    Vector2f GetScale() override { return Vector2f(); }

    Vector2f GetOrigin() override { return Vector2f(); }

    void SetOrigin(const Vector2f& ori) override {}

    Vector2f GetSize() override { return Vector2f(); }

    void SetSize(const Vector2f& size) override {}

    Vector2f GetGlobalSize() override { return Vector2f(); }

    Vector2f GetLocalSize() override { return Vector2f(); }
    void SetLocalSize(const Vector2f& size) override {}
};

