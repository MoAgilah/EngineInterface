#include "Box.h"

#include "../Engine/Core/GameManager.h"

Box::Box(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos)
	: GameObject(std::move(drawable), std::move(volume))
{
	Init(initPos);
}

void Box::Reset()
{
	m_canHit = true;
	m_justHit = false;
	GameObject::Reset();
}

void Box::WasJustHit()
{
	if (m_canHit)
		m_justHit = true;
}

void Box::Init(const Vector2f& initPos)
{
	SetInitialDirection(true);
	SetDirection(GetInitialDirection());
	SetInitialPosition(initPos);
	SetPosition(GetInitialPosition());
	GetVolume()->Update(GetPosition());
}