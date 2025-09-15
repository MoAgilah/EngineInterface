#pragma once

#include "Defines.h"
#include <cstddef>
#include <cmath>
#include <stdexcept>

#if USE_SFML
#include <SFML/Graphics.hpp>
#endif

template<typename T>
class Vector
{
public:
	Vector()
		: x{}, y{}
	{}

	Vector(T x, T y)
		: x(x), y(y)
	{}

#if USE_SFML
	Vector(const sf::Vector<T>& vec)
		: x(vec.x), y(vec.y)
	{}
#endif

	~Vector() = default;

	T& operator[] (std::size_t index)
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		default:	throw std::out_of_range("Vector2f subscript out of range");
		}
	}

	const T& operator[] (std::size_t index) const
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		default:	throw std::out_of_range("Vector2f subscript out of range");
		}
	}

	// --- compound assignment (ONE parameter each) ---
	Vector& operator+=(const Vector& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector& operator-=(const Vector& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

	// scale by scalar
	Vector& operator*=(const T& s) { x *= s;     y *= s;     return *this; }
	Vector& operator/=(const T& s) { x /= s;     y /= s;     return *this; }

	// element-wise by vector (only keep if you already had these)
	Vector& operator*=(const Vector& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
	Vector& operator/=(const Vector& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

	// --- comparisons (must have return type and be const) ---
	bool operator==(const Vector& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Vector& rhs) const { return !(*this == rhs); }

#if USE_SFML
	operator sf::Vector2<T>() const
	{
		return sf::Vector2<T>(x, y);
	}
#endif

	Vector Clamp(const Vector& p1, const Vector& p2) const
	{
		return { std::max(p1.x, std::min(p2.x, x)), std::max(p1.y, std::min(p2.y, y)) };
	}

	T LengthSquared()
	{
		return x * x + y * y;
	}

	T Dot(const Vector& op) const
	{
		return x * op.x + y * op.y;
	}

	T Distance(const Vector& op) const
	{
		return std::sqrtf(std::powf((op.x - x), 2) + std::powf((op.y - y), 2));
	}

	T Length()
	{
		return std::sqrtf(Dot(*this));
	}

	Vector Normalize()
	{
		auto len = Length();
		return Vector(x / len, y / len);
	}

	bool  IsBetween(const Vector& a, const Vector& b)
	{
		// p is between a and b if the dot product of (p - a) and (p - b) is non-positive.
		return ((*this - a).Dot(*this - b)) <= 0.0f;
	}

	T x;
	T y;
};

// vector + vector
template <typename T>
inline Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs) { lhs += rhs; return lhs; }

// vector - vector
template <typename T>
inline Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs) { lhs -= rhs; return lhs; }

// vector * scalar
template <typename T>
inline Vector<T> operator*(Vector<T> lhs, const T& s) { lhs *= s; return lhs; }

// scalar * vector
template <typename T>
inline Vector<T> operator*(const T& s, Vector<T> rhs) { rhs *= s; return rhs; }

// vector / scalar
template <typename T>
inline Vector<T> operator/(Vector<T> lhs, const T& s) { lhs /= s; return lhs; }

// element-wise vector * vector  (only keep if you already had member *= (Vector))
template <typename T>
inline Vector<T> operator*(Vector<T> lhs, const Vector<T>& rhs) { lhs *= rhs; return lhs; }

// element-wise vector / vector  (only keep if you already had member /= (Vector))
template <typename T>
inline Vector<T> operator/(Vector<T> lhs, const Vector<T>& rhs) { lhs /= rhs; return lhs; }

using Vector2i = Vector<int>;
using Vector2u = Vector<unsigned int>;
using Vector2f = Vector<float>;