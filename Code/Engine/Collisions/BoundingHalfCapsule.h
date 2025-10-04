#pragma once

#include "BoundingBox.h"
#include "BoundingCircle.h"
#include "BoundingCapsule.h"
#include "../../Utilities/Vector.h"
#include <algorithm>
#include <cmath>

template <typename PlatformCapsule>
struct HalfCapsule
{
    using PlatformCircle = typename CapsuleTraits<PlatformCapsule>::CircleType;
    using PlatformBox = typename CapsuleTraits<PlatformCapsule>::BoxType;

    enum class Which { Start, End };

    HalfCapsule() = default;

    explicit HalfCapsule(BoundingCapsule<PlatformCapsule>* cap,
        Which which = Which::Start)
    {
        Reset(cap, which);
    }

    void Reset(BoundingCapsule<PlatformCapsule>* cap,
        Which which = Which::Start)
    {
        if (!cap) return;

        const float r = cap->GetRadius();
        const auto  seg = cap->GetSegment();

        // chosen end-cap as a circle
        const Vector2f capCenter = (which == Which::Start) ? seg.start : seg.end;
        m_cap = BoundingCircle<PlatformCircle>(r, capCenter);

        // trimmed body sub-segment
        Vector2f a = seg.start;
        Vector2f b = seg.end;

        const Vector2f ab = b - a;
        const float len2 = ab.x * ab.x + ab.y * ab.y;

        if (len2 > 0.0f) {
            const float invLen = 1.0f / std::sqrt(len2);
            const Vector2f dir = ab * invLen;
            if (which == Which::Start) a = a + dir * r; else b = b - dir * r;
        }

        // AABB of sub-segment expanded by radius (same style as Capsule::ToBoundingBox)
        const float minX = std::min(a.x, b.x) - r;
        const float maxX = std::max(a.x, b.x) + r;
        const float minY = std::min(a.y, b.y) - r;
        const float maxY = std::max(a.y, b.y) + r;

        m_body = BoundingBox<PlatformBox>();
        m_body.Reset({ maxX - minX, maxY - minY });
        m_body.Update((a + b) * 0.5f);
    }

    // Keep both components moving together (preserve their internal offset)
    void Update(const Vector2f& pos)
    {
        const Vector2f delta = pos - GetCenter();
        m_cap.SetCenter(m_cap.GetCenter() + delta);
        m_body.SetCenter(m_body.GetCenter() + delta);
    }

    void Render(IRenderer* r)
    {
        m_body.Render(r);
        m_cap.Render(r);
    }

    // Composite helpers
    Vector2f GetCenter() const { return m_body.GetCenter(); }

    bool Intersects(const Vector2f& p) const
    {
        return m_cap.Intersects(p) || m_body.Intersects(p);
    }

    bool Intersects(IBoundingVolume* v)
    {
        return m_cap.Intersects(v) || m_body.Intersects(v);
    }

    bool IntersectsMoving(IBoundingVolume* v, const Vector2f& va, const Vector2f& vb,
        float& tfirst, float& tlast)
    {
        float tf2, tl2;
        const bool hitCap = m_cap.IntersectsMoving(v, va, vb, tfirst, tlast);
        const bool hitBody = m_body.IntersectsMoving(v, va, vb, tf2, tl2);

        if (hitCap && hitBody) {
            if (tf2 < tfirst) { tfirst = tf2; tlast = tl2; }
            return true;
        }
        if (hitCap)  return true;
        if (hitBody) { tfirst = tf2; tlast = tl2; return true; }
        return false;
    }

    Vector2f GetSeparationVector(IBoundingVolume* v, bool preferCap) {
        return preferCap ? m_cap.GetSeparationVector(v) : m_body.GetSeparationVector(v);
    }

    BoundingCircle<PlatformCircle>& Cap() { return m_cap; }
    const BoundingCircle<PlatformCircle>& Cap() const { return m_cap; }
    BoundingBox<PlatformBox>& Body() { return m_body; }
    const BoundingBox<PlatformBox>& Body() const { return m_body; }

private:
    BoundingBox<PlatformBox>       m_body;
    BoundingCircle<PlatformCircle> m_cap;
};