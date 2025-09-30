#include "GameObject.h"

#include "../Engine/Interface/Scene/IGameObject.h"
#include "../Engine/Core/Constants.h"
#include "../Engine/Core/GameManager.h"

GameObject::GameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: m_drawable(std::move(drawable)), m_volume(std::move(volume))
{
	m_objectID = s_objectNum++;
	SetScale(GameConstants::Scale);
	GameManager::Get()->GetCollisionMgr()->AddCollidable(this);
}

GameObject::~GameObject()
{
	GameManager::Get()->GetCollisionMgr()->RemoveCollidable(this);
}

void GameObject::Render(IRenderer* renderer)
{
	if (m_drawable)
		m_drawable->Render(renderer);
#if defined _DEBUG
	if (m_volume)
		m_volume->Render(renderer);
#endif
}

bool GameObject::Intersects(IGameObject* obj)
{
	return m_volume->Intersects(obj->GetVolume());
}

bool GameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	return m_volume->IntersectsMoving(obj->GetVolume(), Vector2f(0, 0), obj->GetVelocity(), tFirst, tLast);
}

void GameObject::Reset()
{
	SetActive(m_active);
	SetDirection(GetInitialDirection());
	SetPosition(GetInitialPosition());
	m_volume->Update(GetPosition());
}

void GameObject::SetScale(const Vector2f& scale)
{
	m_drawable->SetScale(scale);
	m_volume->SetScale(scale);
}

DynamicGameObject::DynamicGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: GameObject(drawable, volume)
{}

bool DynamicGameObject::Intersects(IGameObject * obj)
{
	float tFirst, tLast;
	return obj->Intersects(this, tFirst, tLast);
}

bool DynamicGameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	return this->GetVolume()->IntersectsMoving(obj->GetVolume(), GetVelocity(), obj->GetVelocity(), tFirst, tLast);
}

void DynamicGameObject::Reset()
{
	GameObject::Reset();
	this->SetVelocity(Vector2f());
	m_onGround = false;
}

void DynamicGameObject::Move(float x, float y)
{
	Move(Vector2f(x, y));
}

void DynamicGameObject::Move(const Vector2f& mov)
{
	SetPrevPosition(GetPosition());

	GetDrawable()->OffsetPosition(mov);

	m_volume->Update(GetPosition());
}
