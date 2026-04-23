#pragma once

#include "Defines.h"
#include "Vector2.h"
#include <type_traits>

#if USE_SFML
namespace sf { template<typename T> class Rect; }
#endif

template<typename T>
struct Rect
{
	using geometry_type = typename std::conditional<std::is_floating_point<T>::value, T, float>::type;

	T m_left;
	T m_top;
	T m_width;
	T m_height;

	Rect(T left, T top, T width, T height)
		: m_left(left), m_top(top), m_width(width), m_height(height)
	{
	}

#if USE_SFML
	Rect(const sf::Rect<T>& r)
		: Rect(r.left, r.top, r.width, r.height)
	{
	}

	operator sf::Rect<T>() const
	{
		return sf::Rect<T>({ m_left, m_top }, { m_width, m_height });
	}
#endif

	Vector2<T> Min() const
	{
		return Vector2<T>(m_left, m_top);
	}

	Vector2<T> Max() const
	{
		return Vector2<T>(m_left + m_width, m_top + m_height);
	}

	Vector2<geometry_type> GetCentre() const
	{
		typedef geometry_type R;

		Vector2<T> min = Min();
		Vector2<T> max = Max();

		return Vector2<R>(
			(static_cast<R>(min.x) + static_cast<R>(max.x)) * static_cast<R>(0.5f),
			(static_cast<R>(min.y) + static_cast<R>(max.y)) * static_cast<R>(0.5f)
		);
	}
};

using FloatRect = Rect<float>;
using IntRect = Rect<int>;