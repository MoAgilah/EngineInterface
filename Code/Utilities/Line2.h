#pragma once

#include "Vector2.h"
#include <cmath>
#include <concepts>
#include <numbers>
#include <type_traits>

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

	template <typename T>
	concept SignedOrFloating = std::signed_integral<T> || std::floating_point<T>;

	template <typename T>
	using GeometryResult_t = std::conditional_t<std::floating_point<T>, T, float>;

	template <SignedOrFloating T>
	constexpr T GetXDist(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return b.x - a.x;
	}

	template <SignedOrFloating T>
	constexpr T GetYDist(const Vector2<T>& a, const Vector2<T>& b) noexcept
	{
		return b.y - a.y;
	}
}

template<typename T>
struct Line2
{
	static_assert(SignedOrFloating<T>, "Line2 requires a signed or floating-point type.");

	using value_type = T;
	using geometry_type = GeometryResult_t<T>;

	Line2() = default;

	Line2(const Vector2<T>& start, const Vector2<T>& end)
		: start(start), end(end)
	{
	}

	Vector2<geometry_type> GetMidPoint() const
	{
		using R = geometry_type;

		return Vector2<R>(
			(static_cast<R>(start.x) + static_cast<R>(end.x)) / static_cast<R>(2),
			(static_cast<R>(start.y) + static_cast<R>(end.y)) / static_cast<R>(2)
		);
	}

	geometry_type CalculateAngle() const
	{
		using R = geometry_type;

		return static_cast<R>(
			std::atan2(
				static_cast<R>(GetYDist(start, end)),
				static_cast<R>(GetXDist(start, end))
			) * (static_cast<R>(180) / std::numbers::pi_v<R>)
			);
	}

	geometry_type SqDistPointSegment(const Vector2<geometry_type>& p) const
	{
		using R = geometry_type;

		Vector2<R> s(static_cast<R>(start.x), static_cast<R>(start.y));
		Vector2<R> e(static_cast<R>(end.x), static_cast<R>(end.y));

		Vector2<R> es = e - s;
		Vector2<R> ps = p - s;
		Vector2<R> pe = p - e;

		auto proj = ps.Dot(es);
		if (proj <= static_cast<R>(0))
			return ps.Dot(ps);

		auto segLen2 = es.Dot(es);
		if (proj >= segLen2)
			return pe.Dot(pe);

		return ps.Dot(ps) - (proj * proj) / segLen2;
	}

	Vector2<geometry_type> ClosestPointOnLineSegment(const Vector2<geometry_type>& pnt) const
	{
		using R = geometry_type;

		Vector2<R> s(static_cast<R>(start.x), static_cast<R>(start.y));
		Vector2<R> e(static_cast<R>(end.x), static_cast<R>(end.y));

		Vector2<R> seg = e - s;
		Vector2<R> v = pnt - s;

		auto segLen2 = seg.LengthSquared();
		if (segLen2 == static_cast<R>(0))
			return s;

		auto t = v.Dot(seg) / segLen2;
		if (t < static_cast<R>(0))
			t = static_cast<R>(0);
		if (t > static_cast<R>(1))
			t = static_cast<R>(1);

		return Vector2<R>(
			s.x + t * seg.x,
			s.y + t * seg.y
		);
	}

	bool IsPointAboveLine(const Vector2<geometry_type>& p) const
	{
		using R = geometry_type;
		return p.y <= static_cast<R>(start.y) - static_cast<R>(1e-4f);
	}

	bool IntersectsPoint(const Vector2<geometry_type>& p) const
	{
		using R = geometry_type;

		Vector2<R> s(static_cast<R>(start.x), static_cast<R>(start.y));
		Vector2<R> e(static_cast<R>(end.x), static_cast<R>(end.y));

		auto d1 = p.Distance(e);
		auto d2 = p.Distance(s);
		auto lineLen = s.Distance(e);

		auto buffer = static_cast<R>(0.1f);
		return d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer;
	}

	T DistX() const
	{
		return end.x - start.x;
	}

	T DistY() const
	{
		return end.y - start.y;
	}

	Vector2<T> start;
	Vector2<T> end;
};

using Line2i = Line2<int>;
using Line2f = Line2<float>;