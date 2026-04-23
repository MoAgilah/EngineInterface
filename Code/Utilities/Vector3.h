#pragma once

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Vector3
{
public:
	Vector3()
		: x{}, y{}, z{}
	{
	}

	Vector3(T x, T y, T z)
		: x(x), y(y), z(z)
	{
	}

	~Vector3() = default;

	T& operator[] (std::size_t index)
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		case 2:		return z;
		default:	throw std::out_of_range("Vector3f subscript out of range");
		}
	}

	const T& operator[] (std::size_t index) const
	{
		switch (index)
		{
		case 0:		return x;
		case 1:		return y;
		case 2:		return z;
		default:	throw std::out_of_range("Vector3f subscript out of range");
		}
	}

	// --- compound assignment (ONE parameter each) ---
	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

	// scale by scalar
	Vector3& operator*=(const T& s) { x *= s; y *= s; z *= s;     return *this; }
	Vector3& operator/=(const T& s) { x /= s; y /= s; z /= s;     return *this; }

	// element-wise by vector (only keep if you already had these)
	Vector3& operator*=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
	Vector3& operator/=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

	// --- comparisons (must have return type and be const) ---
	bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }

	Vector3 Clamp(const Vector3& p1, const Vector3& p2) const
	{
		return {
		std::clamp(x, p1.x, p2.x),
		std::clamp(y, p1.y, p2.y),
		std::clamp(z, p1.z, p2.z)
		};
	}

	T LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	T Dot(const Vector3& op) const
	{
		return x * op.x + y * op.y + z * op.z;
	}

	T Distance(const Vector3& op) const
	{
		T dx = op.x - x;
		T dy = op.y - y;
		T dz = op.z - z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	T Length() const
	{
		return std::sqrtf(Dot(*this));
	}

	template <typename U = T>
		requires std::is_floating_point_v<U>
	Vector3 Normalize() const
	{
		auto len = Length();
		return Vector3(x / len, y / len, z / len);
	}

	// NOTE:
	// This implementation only checks whether the projection of the point lies
	// between a and b using a dot product test.
	// It does NOT verify collinearity, so points off the line segment may return true.
	// Additionally, this implementation is unsafe for unsigned types due to underflow.
	bool  IsBetween(const Vector3& a, const Vector3& b)
	{
		// p is between a and b if the dot product of (p - a) and (p - b) is non-positive.
		return ((*this - a).Dot(*this - b)) <= 0.0f;
	}

	T x;
	T y;
	T z;
};

// vector + vector
template <typename T>
inline Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs) { lhs += rhs; return lhs; }

// vector - vector
template <typename T>
inline Vector3<T> operator-(Vector3<T> lhs, const Vector3<T>& rhs) { lhs -= rhs; return lhs; }

// vector * scalar
template <typename T>
inline Vector3<T> operator*(Vector3<T> lhs, const T& s) { lhs *= s; return lhs; }

// scalar * vector
template <typename T>
inline Vector3<T> operator*(const T& s, Vector3<T> rhs) { rhs *= s; return rhs; }

// vector / scalar
template <typename T>
inline Vector3<T> operator/(Vector3<T> lhs, const T& s) { lhs /= s; return lhs; }

// element-wise vector * vector  (only keep if you already had member *= (Vector))
template <typename T>
inline Vector3<T> operator*(Vector3<T> lhs, const Vector3<T>& rhs) { lhs *= rhs; return lhs; }

// element-wise vector / vector  (only keep if you already had member /= (Vector))
template <typename T>
inline Vector3<T> operator/(Vector3<T> lhs, const Vector3<T>& rhs) { lhs /= rhs; return lhs; }

using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;
using Vector3f = Vector3<float>;