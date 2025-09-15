#pragma once

#include "Defines.h"
#include "Vector.h"

template<typename T>
struct Rect
{
	T m_left;
	T m_top;
	T m_width;
	T m_height;

	Rect(T left, T top, T width, T height)
		:m_left(left), m_top(top), m_width(width), m_height(height)
	{
		m_min = { m_left, m_top };
		m_max = { m_left + m_width, m_top + m_height };
		m_midPoint = { (m_min.x + m_max.x) / static_cast<T>(2),
		(m_min.y + m_max.y) / static_cast<T>(2) };
	}

#if USE_SFML

	Rect(const sf::Rect<T>& r)
		: Rect(r.left, r.top, r.width, r.height)
	{
	}

	operator sf::Rect<T>() const
	{
		return sf::Rect<T>(m_left, m_top, m_width, m_height);
	}
#endif

	Vector<T> Min() const { return m_min; }
	Vector<T> Max() const { return m_max; }
	Vector<T> MidPoint() const { return m_midPoint; }

private:

	Vector<T> m_min;
	Vector<T> m_max;
	Vector<T> m_midPoint;
};

using FloatRect = Rect<float>;
using IntRect = Rect<int>;
using UIntRect = Rect<unsigned int>;