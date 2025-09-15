#include "Utilities.h"

#include "../Engine/Interface/Collisions/IBoundingVolume.h"
#include <array>
#include <numbers>
#include <algorithm>
#include <cmath>


Vector2f Line::GetMidPoint() const
{
	float x = (start.x + end.x) / 2.f;
	float y = (start.y + end.y) / 2.f;

	return Vector2f(x, y);
}

float Line::CalculateAngle() const
{
	float angleInDegrees = atan2f(DistY(), DistX()) * (180.f / std::numbers::pi_v<float>);

	return angleInDegrees;
}

float Line::SqDistPointSegment(const Vector2f& p) const
{
	Vector2f es = end - start;
	Vector2f ps = p - start;
	Vector2f pe = p - end;

	float e = ps.Dot(es);

	// Handle cases where c projects outside ab
	if (e <= 0.0f)
		return ps.Dot(ps);

	float f = es.Dot(es);
	if (e >= f)
		return pe.Dot(pe);

	// Handle cases where c projects onto ab
	return ps.Dot(ps) - e * e / f;
}

Vector2f Line::ClosestPointOnLineSegment(const Vector2f& pnt) const
{
	Vector2f segmentVector = end - start;
	Vector2f pointVector = pnt - start;

	float segmentLengthSquared = segmentVector.LengthSquared();
	if (segmentLengthSquared == 0.0f)
	{
		// The line segment is just a single point
		return start;
	}

	// Compute projection factor t
	float t = pointVector.Dot(segmentVector) / segmentLengthSquared;

	// Clamp t to [0, 1] to ensure the closest point is within the segment
	t = std::clamp(t, 0.0f, 1.0f);

	// Compute the closest point on the segment
	return { start.x + t * segmentVector.x, start.y + t * segmentVector.y };
}


bool Line::IsPointAboveLine(const Vector2f& pnt) const
{
	float s = (end.x - start.x) * (pnt.y - start.y) - (end.y - start.y) * (pnt.x - start.x);
	return s > 0;
}

bool Line::IntersectsPoint(const Vector2f& pnt) const
{
	// get distance from the point to the two ends of the line
	float d1 = pnt.Distance(end);
	float d2 = pnt.Distance(start);

	float lineLen = start.Distance(end);

	// a little buffer zone that will give collision
	float buffer = 0.1f;    // higher # = less accurate

	// if the two distances are equal to the line's
	// length, the point is on the line!
	return d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer;
}

bool Line::IntersectsMoving(IBoundingCircle* circle, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) const
{
	// Get relative velocity vector
	Vector2f relativeVelocity = vb - va;

	// Calculate relative movement of the line endpoints
	Vector2f relStartVelocity = relativeVelocity + (start - end);
	Vector2f relEndVelocity = relativeVelocity + (end - start);

	// Calculate the coefficients for the quadratic equation
	float radiusSquared = circle->GetRadius() * circle->GetRadius();

	// From start to circle center
	Vector2f lineToCircleStart = circle->GetCenter() - start;

	float a = relStartVelocity.Dot(relStartVelocity);
	float b = 2 * relStartVelocity.Dot(lineToCircleStart);
	float c = lineToCircleStart.Dot(lineToCircleStart) - radiusSquared;

	// Solve the quadratic equation
	if (!SolveQuadratic(a, b, c, tfirst, tlast))
		return false;  // No intersection

	// Ensure tfirst and tlast are within valid range [0, 1]
	tfirst = std::max(tfirst, 0.0f);
	tlast = std::min(tlast, 1.0f);

	if (tfirst > tlast) return false;

	// Check intersection for line endpoints
	for (float t = tfirst; t <= tlast; t += 0.01f)
	{
		Vector2f currentStart = start + relStartVelocity * t;
		Vector2f currentEnd = end + relEndVelocity * t;
		Vector2f currentCircle = circle->GetCenter() + relativeVelocity * t;

		if ((currentCircle - currentStart).LengthSquared() <= radiusSquared ||
			(currentCircle - currentEnd).LengthSquared() <= radiusSquared) {
			return true;
		}
	}

	return true;
}

float GetXDist(const Vector2f& p1, const Vector2f& p2)
{
	return p2.x - p1.x;
}

float GetYDist(const Vector2f& p1, const Vector2f& p2)
{
	return p2.y - p1.y;
}

bool SolveQuadratic(float a, float b, float c, float& t0, float& t1)
{
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return false;

	float sqrtDiscriminant = std::sqrt(discriminant);
	t0 = (-b - sqrtDiscriminant) / (2.0f * a);
	t1 = (-b + sqrtDiscriminant) / (2.0f * a);
	return true;
}