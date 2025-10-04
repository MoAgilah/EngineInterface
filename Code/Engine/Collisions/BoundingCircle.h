#pragma once

#include "BoundingBox.h"
#include "../Interface/Collisions/IBoundingVolume.h"
#include "../Interface/Collisions/ICollisionManager.h"
#include "../Interface/Drawables/IShape.h"
#include "../../Utilities/Traits.h"

template <typename PlatformCircle>
class BoundingCircle : public IBoundingCircle, public BoundingVolume<PlatformCircle>
{
public:
    BoundingCircle()
        : IBoundingVolume(VolumeType::Circle)
        , IBoundingCircle()
        , BoundingVolume<PlatformCircle>(VolumeType::Circle)
    {
        this->m_shape = std::make_shared<PlatformCircle>();
    }

    BoundingCircle(float radius)
        : IBoundingVolume(VolumeType::Circle)
        , IBoundingCircle()
        , BoundingVolume<PlatformCircle>(VolumeType::Circle)
    {
        this->m_shape = std::make_shared<PlatformCircle>();
        Reset(radius);
    }

    BoundingCircle(float radius, const Vector2f& pos)
        : IBoundingVolume(VolumeType::Circle)
        , IBoundingCircle()
        , BoundingVolume<PlatformCircle>(VolumeType::Circle)
    {
        this->m_shape = std::make_shared<PlatformCircle>();
        Reset(radius);
        Update(pos);
    }

    void Reset(float radius)
    {
        this->m_shape->Reset(radius);
    }

    void Update(const Vector2f& pos) override
    {
        this->m_shape->Update(pos);
    }

    void Render(IRenderer* r) override { BoundingVolume<PlatformCircle>::Render(r); }
    void* GetNativeShape() override { return BoundingVolume<PlatformCircle>::GetNativeShape(); }

    Vector2f GetCenter() const override { return BoundingVolume<PlatformCircle>::GetCenter(); }
    void SetCenter(const Vector2f& c) override { BoundingVolume<PlatformCircle>::SetCenter(c); }

    Vector2f GetPosition() const override { return BoundingVolume<PlatformCircle>::GetPosition(); }
    void SetPosition(const Vector2f& p) override { BoundingVolume<PlatformCircle>::SetPosition(p); }

    Vector2f GetOrigin() const override { return BoundingVolume<PlatformCircle>::GetOrigin(); }
    void SetOrigin(const Vector2f& o) override { BoundingVolume<PlatformCircle>::SetOrigin(o); }

    Vector2f GetScale() const override { return BoundingVolume<PlatformCircle>::GetScale(); }
    void SetScale(const Vector2f& scale) override
    {
        BoundingVolume<PlatformCircle>::SetScale(scale);
        if (this->m_shape)
            Reset(this->m_shape->GetRadius());
    }

    float GetRadius() const override
    {
        ICircleShape* radiusShape = dynamic_cast<ICircleShape*>(this->m_shape.get());
        if (radiusShape)
            return radiusShape->GetRadius() * BoundingVolume<PlatformCircle>::GetScale().x;
        return 0.f;
    }

    bool Intersects(const Vector2f& pnt) const override
    {
        // get distance between the point and circle's center
        // using the Pythagorean Theorem
        Vector2f dist = pnt - BoundingVolume<PlatformCircle>::GetCenter();;

        float distance = dist.Length();

        // if the distance is less than the circle's
        // radius the point is inside!
        return distance <= this->GetRadius();
    }

    bool IntersectsMoving(const Linef& line, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) const
    {
        Vector2f relativeVelocity = vb - va;

        Vector2f relStartVelocity = relativeVelocity + (line.start - line.end);
        Vector2f relEndVelocity = relativeVelocity + (line.end - line.start);

        float radius = GetRadius();
        float radiusSquared = radius * radius;

        Vector2f lineToCircleStart = GetCenter() - line.start;

        float a = relStartVelocity.Dot(relStartVelocity);
        float b = 2.0f * relStartVelocity.Dot(lineToCircleStart);
        float c = lineToCircleStart.Dot(lineToCircleStart) - radiusSquared;

        if (!SolveQuadratic(a, b, c, tfirst, tlast))
            return false;

        tfirst = std::max(tfirst, 0.0f);
        tlast = std::min(tlast, 1.0f);
        if (tfirst > tlast) return false;

        for (float t = tfirst; t <= tlast; t += 0.01f) {
            Vector2f currentStart = line.start + relStartVelocity * t;
            Vector2f currentEnd = line.end + relEndVelocity * t;
            Vector2f currentCenter = GetCenter() + relativeVelocity * t;

            if ((currentCenter - currentStart).LengthSquared() <= radiusSquared ||
                (currentCenter - currentEnd).LengthSquared() <= radiusSquared) {
                return true;
            }
        }
        return true;
    }

    bool Intersects(IBoundingVolume* v) override
    {
        switch (v->GetType())
        {
        case VolumeType::Box:      if (auto* p = dynamic_cast<IBoundingBox*>(v))     return Intersects(p); break;
        case VolumeType::Circle:   if (auto* p = dynamic_cast<IBoundingCircle*>(v))  return Intersects(p); break;
        case VolumeType::Capsule:  if (auto* p = dynamic_cast<IBoundingCapsule*>(v)) return Intersects(p); break;
        default: break;
        }
        return false;
    }

    bool IntersectsMoving(IBoundingVolume* v, const Vector2f& va, const Vector2f& vb,
        float& tfirst, float& tlast) override
    {
        switch (v->GetType())
        {
        case VolumeType::Box:     if (auto* p = dynamic_cast<IBoundingBox*>(v))     return IntersectsMoving(p, va, vb, tfirst, tlast); break;
        case VolumeType::Circle:  if (auto* p = dynamic_cast<IBoundingCircle*>(v))  return IntersectsMoving(p, va, vb, tfirst, tlast); break;
        case VolumeType::Capsule: if (auto* p = dynamic_cast<IBoundingCapsule*>(v)) return IntersectsMoving(p, va, vb, tfirst, tlast); break;
        default: break;
        }
        return false;
    }

    Vector2f GetSeparationVector(IBoundingVolume* v) override
    {
        switch (v->GetType()) {
        case VolumeType::Box:     if (auto* p = dynamic_cast<IBoundingBox*>(v))     return GetSeparationVector(p); break;
        case VolumeType::Circle:  if (auto* p = dynamic_cast<IBoundingCircle*>(v))  return GetSeparationVector(p); break;
        case VolumeType::Capsule: if (auto* p = dynamic_cast<IBoundingCapsule*>(v)) return GetSeparationVector(p); break;
        default: break;
        }
        return {};
    }


    Vector2f GetPoint(Side side) override
    {
        auto center = BoundingVolume<PlatformCircle>::GetCenter();
        auto radius = GetRadius();
        switch (side) {
        case Side::Left:   return center - Vector2f(radius, 0);
        case Side::Right:  return center + Vector2f(radius, 0);
        case Side::Top:    return center - Vector2f(0, radius);
        case Side::Bottom: return center + Vector2f(0, radius);
        }
        return {};
    }

protected:

    bool Intersects(IBoundingBox* box) override
    {
        return box->Intersects(static_cast<IBoundingVolume*>(this));
    }

    bool Intersects(IBoundingCircle* circle) override
    {
        // Calculate squared distance between centers
        Vector2f d = this->GetCenter() - circle->GetCenter();
        float dist2 = d.Dot(d);

        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = this->GetRadius() + circle->GetRadius();
        return dist2 <= radiusSum * radiusSum;
    }

    bool Intersects(IBoundingCapsule* capsule) override
    {
        float r = this->GetRadius() + capsule->GetRadius();

        float distSq = capsule->GetSegment().SqDistPointSegment(this->GetCenter());

        return distSq <= r * r;
    }

    bool IntersectsMoving(IBoundingBox* box, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        return box->IntersectsMoving(static_cast<IBoundingVolume*>(this), va, vb, tfirst, tlast);
    }

    bool IntersectsMoving(IBoundingCircle* circle, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        Vector2f s = this->GetCenter() - circle->GetCenter();
        float r = circle->GetRadius() + this->GetRadius();

        Vector2f v = vb - va; // Relative motion
        float a = v.Dot(v);

        if (a < ICollisionManager::EPSILON) return false; // No relative motion

        float b = v.Dot(s);
        if (b >= 0.0f) return false; // Moving away

        float c = s.Dot(s) - r * r;
        if (c < -ICollisionManager::EPSILON) // Initial overlap case
        {
            tfirst = tlast = 0.0f;
            return true;
        }

        float d = b * b - a * c;
        if (d < 0.0f) return false; // No real solution

        float sqrtD = std::sqrt(d);
        tfirst = (-b - sqrtD) / a;
        tlast = (-b + sqrtD) / a;

        if (tlast < 0.0f || tfirst > 1.0f) return false;
        if (tfirst > tlast) return false;

        // If tfirst is negative, clamp to zero
        if (tfirst < 0.0f && tlast >= 0.0f)
            tfirst = 0.0f;

        return true;
    }

    bool IntersectsMoving(IBoundingCapsule* capsule, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        return capsule->IntersectsMoving(static_cast<IBoundingVolume*>(this), va, vb, tfirst, tlast);
    }

    Vector2f GetSeparationVector(IBoundingBox* box) override
    {
        return box->GetSeparationVector(static_cast<IBoundingVolume*>(this));
    }

    Vector2f GetSeparationVector(IBoundingCircle* other) override
    {
        Vector2f displacement = other->GetPosition() - GetPosition();
        float distance = displacement.Length();
        float radiusSum = other->GetRadius() + GetRadius();
        float penetrationDepth = radiusSum - distance;

        if (penetrationDepth > 0.0f && distance > std::numeric_limits<float>::epsilon())
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

        if (distance <= std::numeric_limits<float>::epsilon())
            return { 0.f, (other->GetPosition().y > GetPosition().y ? 1.f : -1.f) * (radiusSum + ICollisionManager::BUFFER) };

        return Vector2f();
    }

    Vector2f GetSeparationVector(IBoundingCapsule* other) override
    {
        Vector2f closestPoint = other->GetSegment().ClosestPointOnLineSegment(GetPosition());
        Vector2f displacement = GetPosition() - closestPoint;
        float distance = displacement.Length();
        float radiusSum = GetRadius() + other->GetRadius();
        float penetrationDepth = radiusSum - distance;

        if (penetrationDepth > 0.0f && distance > std::numeric_limits<float>::epsilon())
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

        if (distance <= std::numeric_limits<float>::epsilon())
            return { 0.f, (GetPosition().y > other->GetPosition().y ? 1.f : -1.f) * (radiusSum + ICollisionManager::BUFFER) };

        return Vector2f();
    }
};
