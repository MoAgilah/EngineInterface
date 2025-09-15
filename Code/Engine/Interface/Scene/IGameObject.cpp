#include "IGameObject.h"

int IGameObject::s_objectNum = 0;

void IDynamicGameObject::SetOnSlope(bool slp)
{
	m_onSlope = slp;
	if (m_onSlope)
		m_onGround = true;
}

void IDynamicGameObject::SetShouldSlideLeft(bool left)
{
	m_shouldSlideLeft = left;
	if (m_shouldSlideLeft)
		m_shouldSlideRight = false;
}

void IDynamicGameObject::SetSlideLeft(bool left)
{
	m_slideLeft = left;
	if (m_slideLeft)
		m_slideRight = false;
}

void IDynamicGameObject::SetShouldSlideRight(bool right)
{
	m_shouldSlideRight = right;
	if (m_shouldSlideRight)
		m_shouldSlideLeft = false;
}

void IDynamicGameObject::SetSlideRight(bool right)
{
	m_slideRight = right;
	if (m_slideRight)
		m_slideLeft = false;
}

Direction IDynamicGameObject::GetFacingDirection()
{
	const Vector2f& vel = m_velocity;
	if (vel.x == 0.f && vel.y == 0.f)
		return Direction::DDIR;

	return (std::abs(vel.x) > std::abs(vel.y))
		? (vel.x < 0 ? Direction::LDIR : Direction::RDIR)
		: (vel.y < 0 ? Direction::UDIR : Direction::DDIR);
}