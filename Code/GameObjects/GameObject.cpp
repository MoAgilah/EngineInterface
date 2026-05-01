#include "GameObject.h"

#include "../Engine/Interface/Scene/IGameObject.h"
#include "../Engine/Core/Constants.h"
#include "../Engine/Core/GameManager.h"
#include "../Utilities/Guards.h"

GameObject::GameObject()
	: m_drawable(nullptr), m_volume(nullptr)
{
	m_objectID = s_objectNum++;
}

GameObject::GameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: m_drawable(std::move(drawable)), m_volume(std::move(volume))
{
	if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
		throw std::invalid_argument("GameObject requires a valid drawable");

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		throw std::invalid_argument("GameObject requires a valid volume");

	m_objectID = s_objectNum++;
	SetScale(GameConstants::Scale);

	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		throw std::runtime_error("GameObject requires a valid GameManager");

	auto* colMgr = gameMgr->GetCollisionMgr();
	if (!CheckNotNull(colMgr, "Invalid Pointer 'colMgr' from gameMgr->GetCollisionMgr()"))
		throw std::runtime_error("GameObject requires a valid CollisionManager");

	colMgr->AddCollidable(this);
}

GameObject::~GameObject()
{
	auto* gameMgr = GameManager::Get();
	if (!gameMgr)
		return;

	auto* colMgr = gameMgr->GetCollisionMgr();
	if (!colMgr)
		return;

	colMgr->RemoveCollidable(this);
}

void GameObject::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

	if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
		return;

	m_drawable->Render(renderer);
#if defined _DEBUG

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return;

	m_volume->Render(renderer);
#endif
}

bool GameObject::Intersects(IGameObject* obj)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return false;

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return false;

	return m_volume->Intersects(obj->GetVolume());
}

bool GameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return false;

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return false;

	return m_volume->IntersectsMoving(obj->GetVolume(), Vector2f(0, 0), obj->GetVelocity(), tFirst, tLast);
}

void GameObject::Reset()
{
	SetActive(m_active);
	SetDirection(GetInitialDirection());
	SetPosition(GetInitialPosition());

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return;

	m_volume->Update(GetPosition());
}

void GameObject::SetScale(const Vector2f& scale)
{
	if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
		return;

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return;

	m_drawable->SetScale(scale);
	m_volume->SetScale(scale);
}

DynamicGameObject::DynamicGameObject()
{
}

DynamicGameObject::DynamicGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume)
	: GameObject(drawable, volume)
{}

bool DynamicGameObject::Intersects(IGameObject * obj)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return false;

	float tFirst, tLast;
	return obj->Intersects(this, tFirst, tLast);
}

bool DynamicGameObject::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return false;

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return false;

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
	if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
		return;

	if (!CheckNotNull(m_volume.get(), "Invalid Pointer 'm_volume'"))
		return;

	SetPrevPosition(GetPosition());

	m_drawable->OffsetPosition(mov);

	m_volume->Update(GetPosition());
}
