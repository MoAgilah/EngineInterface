#pragma once

#include "../Interface/Collisions/ICollisionManager.h"
#include "../Interface/Drawables/IShape.h"
#include "../Interface/Collisions/IBoundingVolume.h"
#include "../../Utilities/Traits.h"
#include <algorithm>

template <typename PlatformBox>
class BoundingBox : public IBoundingBox, public BoundingVolume<PlatformBox>
{
public:
    BoundingBox()
        : IBoundingVolume(VolumeType::Box)
        , IBoundingBox()
        , BoundingVolume<PlatformBox>(VolumeType::Box)
    {
        this->m_shape = std::make_shared<PlatformBox>();
    }

    // Only call the virtual base constructor here, not in any parent!
    BoundingBox(const Vector2f& size, const Vector2f& pos)
        : IBoundingVolume(VolumeType::Box)
        , IBoundingBox()
        , BoundingVolume<PlatformBox>(VolumeType::Box)
    {
        this->m_shape = std::make_shared<PlatformBox>();
        Reset(size);
        Update(pos);
    }

    void Reset(const Vector2f& size)
    {
        this->m_shape->Reset(size);
        auto scale = GetScale();
        m_extents = { size.x * 0.5f * scale.x, size.y * 0.5f * scale.y };
    }

    void Update(const Vector2f& pos) override
    {
        this->m_shape->Update(pos);
        auto center = BoundingVolume<PlatformBox>::GetCenter();
        m_min = center - m_extents;
        m_max = center + m_extents;
    }

    void Render(IRenderer* r) override { BoundingVolume<PlatformBox>::Render(r); }
    void* GetNativeShape() override { return BoundingVolume<PlatformBox>::GetNativeShape(); }

    Vector2f GetCenter() const override { return BoundingVolume<PlatformBox>::GetCenter(); }
    void SetCenter(const Vector2f& c) override { BoundingVolume<PlatformBox>::SetCenter(c); }

    Vector2f GetPosition() const override { return BoundingVolume<PlatformBox>::GetPosition(); }
    void SetPosition(const Vector2f& p) override { BoundingVolume<PlatformBox>::SetPosition(p); }

    Vector2f GetOrigin() const override { return BoundingVolume<PlatformBox>::GetOrigin(); }
    void SetOrigin(const Vector2f& o) override { BoundingVolume<PlatformBox>::SetOrigin(o); }

    Vector2f GetScale() const override { return BoundingVolume<PlatformBox>::GetScale(); }
    void SetScale(const Vector2f& scale) override
    {
        BoundingVolume<PlatformBox>::SetScale(scale);
        if (this->m_shape)
            Reset(this->m_shape->GetSize());
    }

    float SqDistPoint(const Vector2f& p) const
    {
        float sqDist = 0.0f;
        for (size_t i = 0; i < 2; i++)
        {
            float v = p[i];
            if (v < m_min[i]) sqDist += (m_min[i] - v) * (m_min[i] - v);
            if (v > m_max[i]) sqDist += (v - m_max[i]) * (v - m_max[i]);
        }
        return sqDist;
    }

    bool Intersects(const Vector2f& pnt) const override
    {
        return (pnt.x >= m_min.x && pnt.x <= m_max.x &&
            pnt.y >= m_min.y && pnt.y <= m_max.y);
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
        auto center = BoundingVolume<PlatformBox>::GetCenter();
        switch (side) {
        case Side::Top:    return Vector2f(center.x, m_min.y);
        case Side::Bottom: return Vector2f(center.x, m_max.y);
        case Side::Left:   return Vector2f(m_min.x, center.y);
        case Side::Right:  return Vector2f(m_max.x, center.y);
        }
        return Vector2f();
    }

    Linef GetSide(Side side) override
    {
        switch (side)
        {
        case Side::Left:    return Linef(m_min, Vector2f(m_min.x, m_max.y));
        case Side::Right:   return Linef(Vector2f(m_max.x, m_min.y), m_max);
        case Side::Top:     return Linef(m_min, Vector2f(m_max.x, m_min.y));
        case Side::Bottom:  return Linef(Vector2f(m_min.x, m_max.y), m_max);
        }
        return Linef();
    }

protected:

    bool Intersects(IBoundingBox* box) override
    {
        for (size_t i = 0; i < 2; i++)
        {
            if (std::abs(this->GetCenter()[i] - box->GetCenter()[i])
        > m_extents[i] + box->GetExtents()[i])
                return false;
        }

        // Overlapping on all axes means AABBs are intersecting
        return true;
    }

    bool Intersects(IBoundingCircle* circle) override
    {
        // Compute squared distance between sphere center and AABB
        float sqDist = SqDistPoint(circle->GetCenter());
        float radius = circle->GetRadius();

        // Sphere and AABB intersect if the (squared) distance
        // between them is less than the (squared) sphere radius
        return sqDist <= radius * radius;
    }

    bool Intersects(IBoundingCapsule* capsule) override
    {
        // Compute the box's min and max corners
        Vector2f boxMin = m_min;
        Vector2f boxMax = m_max;

        const auto& line = capsule->GetSegment();

        // Check the line segment (capsule core) against the box
        Vector2f closestToStart = line.start.Clamp(boxMin, boxMax);
        Vector2f closestToEnd = line.end.Clamp(boxMin, boxMax);

        float distStart = line.SqDistPointSegment(closestToStart);
        float distEnd = line.SqDistPointSegment(closestToEnd);

        float radSq = capsule->GetRadius() * capsule->GetRadius();

        // Check if the distances are less than or equal to the capsule's radius squared
        if (distStart <= radSq || distEnd <= radSq)
            return true;

        float closestPointStartDistSq = (closestToStart - line.start).LengthSquared();
        float closestPointEndDistSq = (closestToEnd - line.end).LengthSquared();

        return closestPointStartDistSq <= radSq || closestPointEndDistSq <= radSq;
    }

    bool IntersectsMoving(IBoundingBox* box, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        if (Intersects(box))
        {
            tfirst = tlast = 0.0f;
            return true;
        }

        Vector2f v = vb - va;
        if (std::abs(v.x) < ICollisionManager::EPSILON && std::abs(v.y) < ICollisionManager::EPSILON)
            return false;

        tfirst = 0.0f;
        tlast = 1.0f;

        for (int i = 0; i < 2; i++)
        {
            if (std::abs(v[i]) < ICollisionManager::EPSILON)
            {
                if (box->GetMax()[i] < m_min[i] || box->GetMin()[i] > m_max[i])
                    return false;

                continue;
            }

            if (v[i] < 0.0f)
            {
                if (box->GetMax()[i] < m_min[i] && v[i] <= 0.0f) return false;
                if (m_max[i] <= box->GetMin()[i]) tfirst = std::max((m_max[i] - box->GetMin()[i]) / v[i], tfirst);
                if (box->GetMax()[i] >= m_min[i]) tlast = std::min((m_min[i] - box->GetMax()[i]) / v[i], tlast);
            }
            else if (v[i] > 0.0f)
            {
                if (box->GetMin()[i] > m_max[i] && v[i] >= 0.0f) return false;
                if (box->GetMax()[i] <= m_min[i]) tfirst = std::max((m_min[i] - box->GetMax()[i]) / v[i], tfirst);
                if (m_max[i] >= box->GetMin()[i]) tlast = std::min((m_max[i] - box->GetMin()[i]) / v[i], tlast);
            }
        }

        if (tfirst > tlast)
            return false;

        return true;
    }

    bool IntersectsMoving(IBoundingCircle* circle, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        // Calculate relative velocity: circle's motion relative to the box
        Vector2f relativeVelocity = vb - va;

        // No movement → fall back to static check
        if (relativeVelocity.LengthSquared() < ICollisionManager::EPSILON * ICollisionManager::EPSILON)
            return Intersects(circle);

        // Treat the circle as a moving point by expanding the box by the radius
        float r = circle->GetRadius();
        Vector2f boxMin = GetMin() - Vector2f(r, r);
        Vector2f boxMax = GetMax() + Vector2f(r, r);

        Vector2f invVelocity = {
            std::abs(relativeVelocity.x) > ICollisionManager::EPSILON ? 1.f / relativeVelocity.x : 0.f,
            std::abs(relativeVelocity.y) > ICollisionManager::EPSILON ? 1.f / relativeVelocity.y : 0.f
        };

        float tEnterX = (boxMin.x - circle->GetPosition().x) * invVelocity.x;
        float tExitX = (boxMax.x - circle->GetPosition().x) * invVelocity.x;
        if (invVelocity.x < 0.f) std::swap(tEnterX, tExitX);

        float tEnterY = (boxMin.y - circle->GetPosition().y) * invVelocity.y;
        float tExitY = (boxMax.y - circle->GetPosition().y) * invVelocity.y;
        if (invVelocity.y < 0.f) std::swap(tEnterY, tExitY);

        float entryTime = std::max(tEnterX, tEnterY);
        float exitTime = std::min(tExitX, tExitY);

        // Reject if exit before entry, or exit is in the past, or entry is too far in future
        if (entryTime > exitTime || exitTime < -ICollisionManager::EPSILON || entryTime > 1.0f)
            return false;

        // ✅ Allow t=0 contact as a valid collision
        tfirst = std::max(0.f, entryTime);
        tlast = std::min(1.f, exitTime);
        return true;
    }

    bool IntersectsMoving(IBoundingCapsule* capsule, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
    {
        return capsule->IntersectsMoving(static_cast<IBoundingVolume*>(this), va, vb, tfirst, tlast);
    }

    Vector2f GetSeparationVector(IBoundingBox* other) override
    {
        Vector2f delta = other->GetPosition() - GetPosition();
        delta = { std::abs(delta.x), std::abs(delta.y) };
        Vector2f overlap = (other->GetExtents() + m_extents) - delta;

        if (overlap.x < overlap.y)
        {
            float direction = (other->GetPosition().x < GetPosition().x) ? -1.0f : 1.0f;
            return { (overlap.x + ICollisionManager::BUFFER) * direction, 0 };
        }
        else
        {
            float direction = (other->GetPosition().y < GetPosition().y) ? -1.0f : 1.0f;
            return { 0, (overlap.y + ICollisionManager::BUFFER) * direction };
        }
    }

    Vector2f GetSeparationVector(IBoundingCircle* other) override
    {
        Vector2f circlePos = other->GetPosition();
        Vector2f closestPoint = {
            std::max(m_min.x, std::min(circlePos.x, m_max.x)),
            std::max(m_min.y, std::min(circlePos.y, m_max.y))
        };

        Vector2f displacement = circlePos - closestPoint;
        float distance = displacement.Length();
        float penetrationDepth = other->GetRadius() - distance;

        // If overlapping and distance is meaningful
        if (penetrationDepth > 0.f && distance > std::numeric_limits<float>::epsilon())
        {
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);
        }

        // If the circle's center is inside the box (distance ≈ 0), pick an arbitrary direction
        if (distance <= std::numeric_limits<float>::epsilon())
        {
            // Choose vertical push direction based on position relative to box center
            float pushDir = (circlePos.y < this->GetCenter().y) ? -1.f : 1.f;
            return Vector2f(0.f, pushDir * (other->GetRadius() + ICollisionManager::BUFFER));
        }

        // No collision
        return Vector2f();
    }

    Vector2f GetSeparationVector(IBoundingCapsule* other) override
    {
        Vector2f closestPoint = other->GetSegment().ClosestPointOnLineSegment(this->GetCenter());
        Vector2f clampedPoint = {
            std::max(m_min.x, std::min(closestPoint.x, m_max.x)),
            std::max(m_min.y, std::min(closestPoint.y, m_max.y))
        };

        Vector2f displacement = closestPoint - clampedPoint;
        float distance = displacement.Length();
        float penetrationDepth = other->GetRadius() - distance;

        if (penetrationDepth > 0.0f && distance > std::numeric_limits<float>::epsilon())
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

        if (distance <= std::numeric_limits<float>::epsilon())
        {
            Vector2f centerDelta = other->GetPosition() - this->GetCenter();
            if (std::abs(centerDelta.y) > std::abs(centerDelta.x))
                return { 0.f, (centerDelta.y > 0.f ? 1.f : -1.f) * (other->GetRadius() + ICollisionManager::BUFFER) };
            else
                return { (centerDelta.x > 0.f ? 1.f : -1.f) * (other->GetRadius() + ICollisionManager::BUFFER), 0.f };
        }

        return Vector2f();
    }
};