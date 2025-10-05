#include "GameObject.h"

#include "../Engine/Interface/Scene/IGameObject.h"
#include "../Engine/Core/Constants.h"
#include "../Engine/Core/GameManager.h"
#include "../Utilities/Utils.h"

GameObject::GameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: m_drawable(std::move(drawable)), m_volume(std::move(volume))
{
	ENSURE_VALID(m_drawable);
	ENSURE_VALID(m_volume);
	m_objectID = s_objectNum++;
	SetScale(GameConstants::Scale);
	GET_OR_RETURN(gameMgr, GameManager::Get());
	GET_OR_RETURN(colMgr, gameMgr->GetCollisionMgr());
	colMgr->AddCollidable(this);
}

GameObject::~GameObject()
{
	GET_OR_RETURN(gameMgr, GameManager::Get());
	GET_OR_RETURN(colMgr, gameMgr->GetCollisionMgr());
	colMgr->RemoveCollidable(this);
}

void GameObject::Render(IRenderer* renderer)
{
	ENSURE_VALID(renderer);
	ENSURE_VALID(m_drawable);
	m_drawable->Render(renderer);
#if defined _DEBUG
	ENSURE_VALID(m_volume);
	m_volume->Render(renderer);
#endif
}

bool GameObject::Intersects(IGameObject* obj)
{
	ENSURE_VALID_RET(obj, false);
	ENSURE_VALID_RET(m_volume, false);
	return m_volume->Intersects(obj->GetVolume());
}

bool GameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	ENSURE_VALID_RET(obj, false);
	ENSURE_VALID_RET(m_volume, false);
	return m_volume->IntersectsMoving(obj->GetVolume(), Vector2f(0, 0), obj->GetVelocity(), tFirst, tLast);
}

void GameObject::Reset()
{
	SetActive(m_active);
	SetDirection(GetInitialDirection());
	SetPosition(GetInitialPosition());
	ENSURE_VALID(m_volume);
	m_volume->Update(GetPosition());
}

void GameObject::SetScale(const Vector2f& scale)
{
	ENSURE_VALID(m_drawable);
	ENSURE_VALID(m_volume);
	m_drawable->SetScale(scale);
	m_volume->SetScale(scale);
}

DynamicGameObject::DynamicGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: GameObject(drawable, volume)
{}

bool DynamicGameObject::Intersects(IGameObject * obj)
{
	ENSURE_VALID_RET(obj,false);
	float tFirst, tLast;
	return obj->Intersects(this, tFirst, tLast);
}

bool DynamicGameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	ENSURE_VALID_RET(obj, false);
	ENSURE_VALID_RET(m_volume, false);
	return m_volume->IntersectsMoving(obj->GetVolume(), GetVelocity(), obj->GetVelocity(), tFirst, tLast);
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
	ENSURE_VALID(m_drawable);
	ENSURE_VALID(m_volume);

	SetPrevPosition(GetPosition());

	m_drawable->OffsetPosition(mov);

	m_volume->Update(GetPosition());
}
