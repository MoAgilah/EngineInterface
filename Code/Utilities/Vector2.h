#pragma once

#include "Defines.h"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

#if USE_SFML
namespace sf { template<typename T> class Vector2; }
#endif

template<typename T>
class Vector2
{
public:
	Vector2()
		: x{}, y{}
	{}

	Vector2(T x, T y)
		: x(x), y(y)
	{}

	~Vector2() = default;

	T& operator[] (std::size_t index)
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		default:	throw std::out_of_range("Vector2 subscript out of range");
		}
	}

	const T& operator[] (std::size_t index) const
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		default:	throw std::out_of_range("Vector2 subscript out of range");
		}
	}

	// --- compound assignment (ONE parameter each) ---
	Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

	// scale by scalar
	Vector2& operator*=(const T& s) { x *= s; y *= s;     return *this; }
	Vector2& operator/=(const T& s) { x /= s; y /= s;     return *this; }

	// element-wise by vector (only keep if you already had these)
	Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
	Vector2& operator/=(const Vector2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

	// --- comparisons (must have return type and be const) ---
	bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Vector2& rhs) const { return !(*this == rhs); }

#if USE_SFML

	// Construct from sf::Vector2<T>
	Vector2(const sf::Vector2<T>& vec)
		: x(vec.x), y(vec.y)
	{
	}

	// Convert to sf::Vector2<T>
	operator sf::Vector2<T>() const
	{
		return sf::Vector2<T>(x, y);
	}

#endif

	Vector2 Clamp(const Vector2& p1, const Vector2& p2) const
	{
		return {
		std::clamp(x, p1.x, p2.x),
		std::clamp(y, p1.y, p2.y),
		};
	}

	T LengthSquared() const
	{
		return x * x + y * y;
	}

	T Dot(const Vector2& op) const
	{
		return x * op.x + y * op.y;
	}

	T Distance(const Vector2& op) const
	{
		T dx = op.x - x;
		T dy = op.y - y;
		return std::sqrt(dx * dx + dy * dy);
	}

	T Length() const
	{
		return std::sqrtf(Dot(*this));
	}

	template <typename U = T>
		requires std::is_floating_point_v<U>
	Vector2 Normalize() const
	{
		auto len = Length();
		return Vector2(x / len, y / len);
	}

	// NOTE:
	// This implementation only checks whether the projection of the point lies
	// between a and b using a dot product test.
	// It does NOT verify collinearity, so points off the line segment may return true.
	// Additionally, this implementation is unsafe for unsigned types due to underflow.
	bool  IsBetween(const Vector2& a, const Vector2& b)
	{
		// p is between a and b if the dot product of (p - a) and (p - b) is non-positive.
		return ((*this - a).Dot(*this - b)) <= 0.0f;
	}

	T x;
	T y;
};

// vector + vector
template <typename T>
inline Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs) { lhs += rhs; return lhs; }

// vector - vector
template <typename T>
inline Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs) { lhs -= rhs; return lhs; }

// vector * scalar
template <typename T>
inline Vector2<T> operator*(Vector2<T> lhs, const T& s) { lhs *= s; return lhs; }

// scalar * vector
template <typename T>
inline Vector2<T> operator*(const T& s, Vector2<T> rhs) { rhs *= s; return rhs; }

// vector / scalar
template <typename T>
inline Vector2<T> operator/(Vector2<T> lhs, const T& s) { lhs /= s; return lhs; }

// element-wise vector * vector  (only keep if you already had member *= (Vector))
template <typename T>
inline Vector2<T> operator*(Vector2<T> lhs, const Vector2<T>& rhs) { lhs *= rhs; return lhs; }

// element-wise vector / vector  (only keep if you already had member /= (Vector))
template <typename T>
inline Vector2<T> operator/(Vector2<T> lhs, const Vector2<T>& rhs) { lhs /= rhs; return lhs; }

// type aliases
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

template <typename V>
concept HasNormalize = requires(const V & v)
{
	{ v.Normalize() } -> std::same_as<V>;
};

static_assert(HasNormalize<Vector2f>, "Vector2f should have Normalize()");
static_assert(!HasNormalize<Vector2i>, "Vector2i should NOT have Normalize()");
static_assert(!HasNormalize<Vector2u>, "Vector2u should NOT have Normalize()");