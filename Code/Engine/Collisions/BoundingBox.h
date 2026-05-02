#pragma once

#include "../Interface/Collisions/ICollisionManager.h"
#include "../Interface/Drawables/IShape.h"
#include "../Interface/Collisions/IBoundingVolume.h"
#include "../../Utilities/Traits.h"
#include "../../Utilities/Guards.h"
#include <algorithm>
#include <stdexcept>
#include <limits>

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
        if (!CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
        {
            throw std::invalid_argument("BoundingBox requires a valid shape");
        }
    }

    BoundingBox(const Vector2f& size)
        : IBoundingVolume(VolumeType::Box)
        , IBoundingBox()
        , BoundingVolume<PlatformBox>(VolumeType::Box)
    {
        this->m_shape = std::make_shared<PlatformBox>();
        if (!CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
        {
            throw std::invalid_argument("BoundingBox requires a valid shape");
        }

        Reset(size);
    }

    // Only call the virtual base constructor here, not in any parent!
    BoundingBox(const Vector2f& size, const Vector2f& pos)
        : IBoundingVolume(VolumeType::Box)
        , IBoundingBox()
        , BoundingVolume<PlatformBox>(VolumeType::Box)
    {
        this->m_shape = std::make_shared<PlatformBox>();
        if (!CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
        {
            throw std::invalid_argument("BoundingBox requires a valid shape");
        }

        Reset(size);
        Update(pos);
    }

    void Reset(const Vector2f& size)
    {
        if (!CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
            return;

        this->m_shape->Reset(size);
        auto scale = GetScale();
        m_extents = { size.x * 0.5f * scale.x, size.y * 0.5f * scale.y };
    }

    void Update(const Vector2f& pos) override
    {
        if (!CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
            return;

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
        if (CheckNotNull(this->m_shape.get(), "Invalid Pointer 'this->m_shape'"))
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
        if (!CheckNotNull(v, "Invalid Pointer 'v'"))
            return false;

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
        if (!CheckNotNull(v, "Invalid Pointer 'v'"))
            return false;

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
        if (!CheckNotNull(v, "Invalid Pointer 'v'"))
            return Vector2f();

        switch (v->GetType())
        {
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
        switch (side)
        {
        case Side::Top:    return Vector2f(center.x, m_min.y);
        case Side::Bottom: return Vector2f(center.x, m_max.y);
        case Side::Left:   return Vector2f(m_min.x, center.y);
        case Side::Right:  return Vector2f(m_max.x, center.y);
        }
        return Vector2f();
    }

    Line2f GetSide(Side side) override
    {
        switch (side)
        {
        case Side::Left:   return Line2f(m_min, Vector2f(m_min.x, m_max.y));
        case Side::Right:  return Line2f(Vector2f(m_max.x, m_min.y), m_max);
        case Side::Top:    return Line2f(m_min, Vector2f(m_max.x, m_min.y));
        case Side::Bottom: return Line2f(Vector2f(m_min.x, m_max.y), m_max);
        }
        return Line2f();
    }

protected:
    bool Intersects(IBoundingBox* box) override
    {
        if (!CheckNotNull(box, "Invalid Pointer 'box'"))
            return false;

        for (size_t i = 0; i < 2; i++)
        {
            if (std::abs(this->GetCenter()[i] - box->GetCenter()[i]) > m_extents[i] + box->GetExtents()[i])
                return false;
        }

        return true;
    }

    bool Intersects(IBoundingCircle* circle) override
    {
        if (!CheckNotNull(circle, "Invalid Pointer 'circle'"))
            return false;

        float sqDist = SqDistPoint(circle->GetCenter());
        float radius = circle->GetRadius();
        return sqDist <= radius * radius;
    }

    bool Intersects(IBoundingCapsule* capsule) override
    {
        if (!CheckNotNull(capsule, "Invalid Pointer 'capsule'"))
            return false;

        Vector2f boxMin = m_min;
        Vector2f boxMax = m_max;

        const auto& line = capsule->GetSegment();

        Vector2f closestToStart = line.start.Clamp(boxMin, boxMax);
        Vector2f closestToEnd = line.end.Clamp(boxMin, boxMax);

        float distStart = line.SqDistPointSegment(closestToStart);
        float distEnd = line.SqDistPointSegment(closestToEnd);

        float radSq = capsule->GetRadius() * capsule->GetRadius();

        if (distStart <= radSq || distEnd <= radSq)
            return true;

        float closestPointStartDistSq = (closestToStart - line.start).LengthSquared();
        float closestPointEndDistSq = (closestToEnd - line.end).LengthSquared();

        return closestPointStartDistSq <= radSq || closestPointEndDistSq <= radSq;
    }

    bool IntersectsMoving(IBoundingBox* box, const Vector2f& va, const Vector2f& vb,
        float& tfirst, float& tlast) override
    {
        if (!CheckNotNull(box, "Invalid Pointer 'box'"))
            return false;

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

        return tfirst <= tlast;
    }

    bool IntersectsMoving(IBoundingCircle* circle, const Vector2f& va, const Vector2f& vb,
        float& tfirst, float& tlast) override
    {
        if (!CheckNotNull(circle, "Invalid Pointer 'circle'"))
            return false;

        Vector2f relativeVelocity = vb - va;

        if (relativeVelocity.LengthSquared() < ICollisionManager::EPSILON * ICollisionManager::EPSILON)
            return Intersects(circle);

        float r = circle->GetRadius();

        Vector2f boxMin = GetMin() - Vector2f(r, r);
        Vector2f boxMax = GetMax() + Vector2f(r, r);

        Vector2f circlePos = circle->GetPosition();

        tfirst = 0.0f;
        tlast = 1.0f;

        for (int i = 0; i < 2; i++)
        {
            if (std::abs(relativeVelocity[i]) < ICollisionManager::EPSILON)
            {
                if (circlePos[i] < boxMin[i] || circlePos[i] > boxMax[i])
                    return false;

                continue;
            }

            float tEnter = (boxMin[i] - circlePos[i]) / relativeVelocity[i];
            float tExit = (boxMax[i] - circlePos[i]) / relativeVelocity[i];

            if (tEnter > tExit)
                std::swap(tEnter, tExit);

            tfirst = std::max(tfirst, tEnter);
            tlast = std::min(tlast, tExit);

            if (tfirst > tlast)
                return false;
        }

        return tfirst <= tlast;
    }

    bool IntersectsMoving(IBoundingCapsule* capsule, const Vector2f& va, const Vector2f& vb,
        float& tfirst, float& tlast) override
    {
        if (!CheckNotNull(capsule, "Invalid Pointer 'capsule'"))
            return false;

        return capsule->IntersectsMoving(static_cast<IBoundingVolume*>(this), va, vb, tfirst, tlast);
    }

    Vector2f GetSeparationVector(IBoundingBox* box) override
    {
        if (!CheckNotNull(box, "Invalid Pointer 'box'"))
            return Vector2f();

        Vector2f delta = box->GetPosition() - GetPosition();

        float overlapX = (box->GetExtents().x + m_extents.x) - std::abs(delta.x);
        float overlapY = (box->GetExtents().y + m_extents.y) - std::abs(delta.y);

        if (overlapX <= 0.0f || overlapY <= 0.0f)
            return Vector2f();

        if (overlapX < overlapY)
        {
            float direction = delta.x < 0.0f ? -1.0f : 1.0f;
            return Vector2f((overlapX + ICollisionManager::BUFFER) * direction, 0.0f);
        }

        float direction = delta.y < 0.0f ? -1.0f : 1.0f;
        return Vector2f(0.0f, (overlapY + ICollisionManager::BUFFER) * direction);
    }

    Vector2f GetSeparationVector(IBoundingCircle* circle) override
    {
        if (!CheckNotNull(circle, "Invalid Pointer 'circle'"))
            return Vector2f();

        Vector2f circlePos = circle->GetPosition();
        Vector2f closestPoint = {
            std::max(m_min.x, std::min(circlePos.x, m_max.x)),
            std::max(m_min.y, std::min(circlePos.y, m_max.y))
        };

        Vector2f displacement = circlePos - closestPoint;
        float distance = displacement.Length();
        float penetrationDepth = circle->GetRadius() - distance;

        if (penetrationDepth > 0.f && distance > std::numeric_limits<float>::epsilon())
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

        if (distance <= std::numeric_limits<float>::epsilon())
        {
            float pushDir = (circlePos.y < this->GetCenter().y) ? -1.f : 1.f;
            return Vector2f(0.f, pushDir * (circle->GetRadius() + ICollisionManager::BUFFER));
        }

        return Vector2f();
    }

    Vector2f GetSeparationVector(IBoundingCapsule* capsule) override
    {
        if (!CheckNotNull(capsule, "Invalid Pointer 'capsule'"))
            return Vector2f();

        Vector2f closestPoint = capsule->GetSegment().ClosestPointOnLineSegment(this->GetCenter());
        Vector2f clampedPoint = {
            std::max(m_min.x, std::min(closestPoint.x, m_max.x)),
            std::max(m_min.y, std::min(closestPoint.y, m_max.y))
        };

        Vector2f displacement = closestPoint - clampedPoint;
        float distance = displacement.Length();
        float penetrationDepth = capsule->GetRadius() - distance;

        if (penetrationDepth > 0.0f && distance > std::numeric_limits<float>::epsilon())
            return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

        if (distance <= std::numeric_limits<float>::epsilon())
        {
            Vector2f centerDelta = capsule->GetPosition() - this->GetCenter();
            if (std::abs(centerDelta.y) > std::abs(centerDelta.x))
                return { 0.f, (centerDelta.y > 0.f ? 1.f : -1.f) * (capsule->GetRadius() + ICollisionManager::BUFFER) };
            else
                return { (centerDelta.x > 0.f ? 1.f : -1.f) * (capsule->GetRadius() + ICollisionManager::BUFFER), 0.f };
        }

        return Vector2f();
    }
};