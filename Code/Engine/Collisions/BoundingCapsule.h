#pragma once

#include "BoundingBox.h"
#include "BoundingCircle.h"
#include "../Interface/Collisions/IBoundingVolume.h"
#include "../Interface/Collisions/ICollisionManager.h"
#include "../Interface/Drawables/IShape.h"
#include "../../Utilities/Traits.h"
#include <algorithm>
#include <numbers>

template <typename PlatformCapsule>
class BoundingCapsule : public IBoundingCapsule, public BoundingVolume<PlatformCapsule>
{
public:
	using PlatformCircle = typename CapsuleTraits<PlatformCapsule>::CircleType;
	using PlatformBox = typename CapsuleTraits<PlatformCapsule>::BoxType;

	BoundingCapsule(float radius, float length, float angle)
		: IBoundingVolume(VolumeType::Capsule)
		, IBoundingCapsule()
		, BoundingVolume<PlatformCapsule>(VolumeType::Capsule)
	{
		this->m_shape = std::make_shared<PlatformCapsule>();
		Reset(radius, length, angle);
	}

	BoundingCapsule(float radius, float length, float angle, const Vector2f& pos)
		: IBoundingVolume(VolumeType::Capsule)
		, IBoundingCapsule()
		, BoundingVolume<PlatformCapsule>(VolumeType::Capsule)
	{
		this->m_shape = std::make_shared<PlatformCapsule>();
		Reset(radius, length, angle);
		Update(pos);
	}

	BoundingCapsule(float radius, const Linef& segment)
		: IBoundingVolume(VolumeType::Capsule)
		, IBoundingCapsule()
		, BoundingVolume<PlatformCapsule>(VolumeType::Capsule)
	{
		this->m_shape = std::make_shared<PlatformCapsule>();
		Reset(radius, segment.start.Distance(segment.end), segment.CalculateAngle());
		Update(segment.GetMidPoint());
	}

	BoundingBox<PlatformBox> ToBoundingBox() const
	{
		BoundingBox<PlatformBox> out;
		const float r = GetRadius();
		const auto& seg = GetSegment();

		const float minX = std::min(seg.start.x, seg.end.x) - r;
		const float maxX = std::max(seg.start.x, seg.end.x) + r;
		const float minY = std::min(seg.start.y, seg.end.y) - r;
		const float maxY = std::max(seg.start.y, seg.end.y) + r;

		out.Reset({ maxX - minX, maxY - minY });
		out.Update(seg.GetMidPoint());
		return out;
	}

	void Reset(float radius, float length, float angle)
	{
		if (this->m_shape)
			this->m_shape->Reset(radius, length, angle);
	}

	void Update(const Vector2f& pos) override
	{
		if (this->m_shape)
			this->m_shape->Update(pos);
	}

	void Render(IRenderer* renderer) override
	{
		if (this->m_shape)
			this->m_shape->Render(renderer);
	}

	void* GetNativeShape() override { return BoundingVolume<PlatformCapsule>::GetNativeShape(); }

	Vector2f GetCenter() const override { return BoundingVolume<PlatformCapsule>::GetCenter(); }
	void SetCenter(const Vector2f& c) override { BoundingVolume<PlatformCapsule>::SetCenter(c); }

	Vector2f GetPosition() const override { return BoundingVolume<PlatformCapsule>::GetPosition(); }
	void SetPosition(const Vector2f& p) override { BoundingVolume<PlatformCapsule>::SetPosition(p); }

	Vector2f GetOrigin() const override { return BoundingVolume<PlatformCapsule>::GetOrigin(); }
	void SetOrigin(const Vector2f& o) override { BoundingVolume<PlatformCapsule>::SetOrigin(o); }

	Vector2f GetScale() const override { return BoundingVolume<PlatformCapsule>::GetScale(); }
	void SetScale(const Vector2f& scale) override
	{
		BoundingVolume<PlatformCapsule>::SetScale(scale);
		if (this->m_shape)
			Reset(GetRadius(), GetLength(), GetAngle());
	}

	float GetRadius() const override
	{
		if (this->m_shape)
			return this->m_shape->GetRadius();

		return 0.f;
	}

	float GetLength() const override
	{
		if (this->m_shape)
			return this->m_shape->GetLength();

		return 0.f;
	}

	float GetAngle()  const override
	{
		if (this->m_shape)
			return this->m_shape->GetAngle();

		return 0.f;
	}

	const Linef GetSegment() const override
	{
		if (this->m_shape)
			return this->m_shape->GetSegment();

		return Linef();
	}

	bool Intersects(const Vector2f& pnt) const override
	{
		auto clsPnt = GetSegment().ClosestPointOnLineSegment(pnt);

		BoundingCircle<PlatformCircle> circle{ GetRadius(), clsPnt };

		return circle.Intersects(pnt);
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
		auto center = BoundingVolume<PlatformCapsule>::GetCenter();
		switch (side) {
		case Side::Top:    return this->GetSegment().start;
		case Side::Bottom: return this->GetSegment().end;
		case Side::Left:   return center - Vector2f(this->GetLength() * 0.5f, 0);
		case Side::Right:  return center + Vector2f(this->GetLength() * 0.5f, 0);
		}
		return center;
	}

protected:

	bool Intersects(IBoundingBox* box) override
	{
		// Compute the box's min and max corners
		Vector2f boxMin = box->GetMin();
		Vector2f boxMax = box->GetMax();

		// Check the line segment (capsule core) against the box
		Vector2f closestToStart = GetSegment().start.Clamp(boxMin, boxMax);
		Vector2f closestToEnd = GetSegment().end.Clamp(boxMin, boxMax);

		float distStart = GetSegment().SqDistPointSegment(closestToStart);
		float distEnd = GetSegment().SqDistPointSegment(closestToEnd);

		float radSq = this->GetRadius() * this->GetRadius();

		// Check if the distances are less than or equal to the capsule's radius squared
		if (distStart <= radSq || distEnd <= radSq)
			return true;

		float closestPointStartDistSq = (closestToStart - GetSegment().start).LengthSquared();
		float closestPointEndDistSq = (closestToEnd - GetSegment().end).LengthSquared();

		return closestPointStartDistSq <= radSq || closestPointEndDistSq <= radSq;
	}

	bool Intersects(IBoundingCircle* circle) override
	{
		float r = circle->GetRadius() + this->GetRadius();

		float dist2 = GetSegment().SqDistPointSegment(circle->GetCenter());

		return dist2 <= r * r;
	}

	bool Intersects(IBoundingCapsule* capsule) override
	{
		float combinedRadiusSquared = (this->GetRadius() + capsule->GetRadius()) * (this->GetRadius() + capsule->GetRadius());

		// Compute the shortest distance squared between the two line segments
		float a = capsule->GetSegment().SqDistPointSegment(this->GetSegment().start);
		float b = capsule->GetSegment().SqDistPointSegment(this->GetSegment().end);
		float c = GetSegment().SqDistPointSegment(capsule->GetSegment().start);
		float d = GetSegment().SqDistPointSegment(capsule->GetSegment().end);

		float distanceSquared = std::min<float>(std::min<float>(a, b), std::min<float>(c, d));

		// Check if the distance is within the combined radii
		return distanceSquared <= combinedRadiusSquared;
	}

	bool IntersectsMoving(IBoundingBox* box, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
	{
		BoundingCircle<PlatformCircle> circle{ GetRadius(), GetSegment().start };
		if (static_cast<IBoundingVolume*>(&circle)->IntersectsMoving(static_cast<IBoundingVolume*>(box), va, vb, tfirst, tlast))
			return true;

		circle.Update(GetSegment().end);

		if (static_cast<IBoundingVolume*>(&circle)->IntersectsMoving(static_cast<IBoundingVolume*>(box), va, vb, tfirst, tlast))
			return true;

		auto capBox = this->ToBoundingBox();
		return static_cast<IBoundingVolume*>(&capBox)->IntersectsMoving(static_cast<IBoundingVolume*>(box), va, vb, tfirst, tlast);
	}

	bool IntersectsMoving(IBoundingCircle* circle, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
	{
		// check the capsule spherical ends
		BoundingCircle<PlatformCircle> capCircle{ circle->GetRadius(), GetSegment().start };

		IBoundingVolume* cc = &capCircle;

		if (cc->IntersectsMoving(static_cast<IBoundingVolume*>(circle), va, vb, tfirst, tlast))
			return true;

		capCircle.Update(GetSegment().end);

		if (cc->IntersectsMoving(static_cast<IBoundingVolume*>(circle), va, vb, tfirst, tlast))
			return true;

		capCircle.Update(GetSegment().GetMidPoint());

		if (cc->IntersectsMoving(static_cast<IBoundingVolume*>(circle), va, vb, tfirst, tlast))
			return true;

		return circle->IntersectsMoving(GetSegment(), va, vb, tfirst, tlast);
	}

	bool IntersectsMoving(IBoundingCapsule* capsule, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) override
	{
		BoundingCircle<PlatformCircle> endpoint1{ GetRadius(), GetSegment().start };
		BoundingCircle<PlatformCircle> endpoint2{ GetRadius(), GetSegment().end };

		BoundingCircle<PlatformCircle> otherEndpoint1{ capsule->GetRadius(), capsule->GetSegment().start };
		BoundingCircle<PlatformCircle> otherEndpoint2{ capsule->GetRadius(), capsule->GetSegment().end };

		IBoundingVolume* e1 = &endpoint1;
		IBoundingVolume* e2 = &endpoint2;
		IBoundingVolume* o1 = &otherEndpoint1;
		IBoundingVolume* o2 = &otherEndpoint2;

		if (e1->IntersectsMoving(o2, va, vb, tfirst, tlast))
			return true;

		if (e2->IntersectsMoving(o1, va, vb, tfirst, tlast))
			return true;

		if (e2->IntersectsMoving(o2, va, vb, tfirst, tlast))
			return true;

		if (e1->IntersectsMoving(o1, va, vb, tfirst, tlast))
			return true;

		BoundingBox<PlatformBox> box1 = this->ToBoundingBox();
		BoundingBox<PlatformBox> box2 = static_cast<BoundingCapsule<PlatformCapsule>*>(capsule)->ToBoundingBox();

		IBoundingVolume* b1 = &box1;
		IBoundingVolume* b2 = &box2;

		return b1->IntersectsMoving(b2, va, vb, tfirst, tlast);
	}

	Vector2f GetSeparationVector(IBoundingBox* box) override
	{
		return box->GetSeparationVector(static_cast<IBoundingVolume*>(this));
	}

	Vector2f GetSeparationVector(IBoundingCircle* circle) override
	{
		return circle->GetSeparationVector(static_cast<IBoundingVolume*>(this));
	}

	Vector2f GetSeparationVector(IBoundingCapsule* other) override
	{
		Vector2f closest1 = GetSegment().ClosestPointOnLineSegment(other->GetSegment().start);
		Vector2f closest2 = other->GetSegment().ClosestPointOnLineSegment(closest1);
		closest1 = GetSegment().ClosestPointOnLineSegment(closest2);

		Vector2f displacement = closest2 - closest1;
		float distance = displacement.Length();
		float radiusSum = GetRadius() + other->GetRadius();
		float penetrationDepth = radiusSum - distance;

		if (penetrationDepth > 0.0f && distance > std::numeric_limits<float>::epsilon())
			return displacement.Normalize() * (penetrationDepth + ICollisionManager::BUFFER);

		if (distance <= std::numeric_limits<float>::epsilon())
			return { 0.f, (other->GetPosition().y > this->GetPosition().y ? 1.f : -1.f) * (radiusSum + ICollisionManager::BUFFER) };

		return Vector2f();
	}
};