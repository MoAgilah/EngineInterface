#pragma once

#include "Vector.h"
#include <concepts>
#include <vector>
#include <numbers>
#include <algorithm>
#include <cmath>

namespace
{
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
}

template<typename T>
struct Line
{
	Line() = default;
	Line(const Vector<T>& start, const Vector<T>& end)
		: start(start), end(end)
	{}

#if USE_SFML
	Line(const sf::ConvexShape& tri, int bgn, int end)
		: Line(tri.getPoint(bgn), tri.getPoint(end))
	{}
#endif

	Vector<T> GetMidPoint() const
	{
		T x = (start.x + end.x) / 2.f;
		T y = (start.y + end.y) / 2.f;

		return Vector<T>(x, y);
	}

	// Return angle (degrees). If T is integral, use double to avoid truncation.
	auto CalculateAngle() const
		-> std::conditional_t<std::is_floating_point_v<T>, T, double>
	{
		using R = std::conditional_t<std::is_floating_point_v<T>, T, double>;
		return static_cast<R>(std::atan2(static_cast<R>(DistY()),
			static_cast<R>(DistX()))
			* (180.0 / std::numbers::pi_v<R>));
	}

	T SqDistPointSegment(const Vector2f& p) const
	{
		Vector<T> es = end - start;
		Vector<T> ps = p - start;
		Vector<T> pe = p - end;

		auto e = ps.Dot(es);
		if (e <= static_cast<T>(0)) return ps.Dot(ps);

		auto f = es.Dot(es);
		if (e >= f)
			return pe.Dot(pe);

		// |ps|^2 - (proj length)^2
		return ps.Dot(ps) - (e * e) / f;
	}

	Vector<T> ClosestPointOnLineSegment(const Vector<T>& pnt) const
	{
		Vector<T> seg = end - start;
		Vector<T> v = pnt - start;

		auto segLen2 = seg.LengthSquared();
		if (segLen2 == static_cast<T>(0))
			return start;

		auto t = v.Dot(seg) / segLen2;
		if (t < static_cast<T>(0)) t = static_cast<T>(0);
		if (t > static_cast<T>(1)) t = static_cast<T>(1);

		return { start.x + t * seg.x, start.y + t * seg.y };
	}

	bool IsPointAboveLine(const Vector<T>& p) const
	{
		// 2D cross product sign
		auto s = (end.x - start.x) * (p.y - start.y)
			- (end.y - start.y) * (p.x - start.x);
		return s > static_cast<T>(0);
	}

	bool IntersectsPoint(const Vector<T>& p) const
	{
		auto d1 = p.Distance(end);
		auto d2 = p.Distance(start);
		auto lineLen = start.Distance(end);

		// small buffer; scale to T
		auto buffer = static_cast<T>(0.1);
		return d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer;
	}

	T DistX() const { return end.x - start.x; }
	T DistY() const { return end.y - start.y; }

	Vector<T> start;
	Vector<T> end;
};

using Linei = Line<int>;
using Lineu = Line<unsigned int>;
using Linef = Line<float>;