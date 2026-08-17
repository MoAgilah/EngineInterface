#include "Collectables.h"

#include "../Engine/Core/GameManager.h"
#include "../Utilities/Guards.h"

StaticCollectable::StaticCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos)
	: GameObject(std::move(drawable), std::move(volume))
{
	Init(initPos);
}

void StaticCollectable::Init(const Vector2f& initPos)
{
	SetInitialActive(true);
	SetActive(GetInitialActive());
	SetInitialDirection(true);
	SetDirection(GetInitialDirection());
	SetInitialPosition(initPos);
	SetPosition(GetInitialPosition());

	auto* drawable = GetDrawable();
	if (!CheckNotNull(drawable, "Invalid Pointer 'drawable' from GetDrawable()"))
		return;

	auto* volume = GetVolume();
	if (!CheckNotNull(volume, "Invalid Pointer 'volume' from GetVolume()"))
		return;

	volume->Update(GetPosition());
}

void StaticCollectable::OnCollisionEnter(IGameObject* obj)
{
}

void StaticCollectable::OnCollisionStay(IGameObject* obj)
{

}

void StaticCollectable::OnCollisionExit(IGameObject* obj)
{

}

void StaticCollectable::ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition)
{

}

DynamicCollectable::DynamicCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos)
	: DynamicGameObject(std::move(drawable), std::move(volume))
{
	Init(initPos);
}

void DynamicCollectable::Init(const Vector2f& initPos)
{
	SetInitialActive(true);
	SetActive(GetInitialActive());
	SetInitialDirection(true);
	SetDirection(GetInitialDirection());
	SetInitialPosition(initPos);
	SetPosition(GetInitialPosition());

	auto* drawable = GetDrawable();
	if (!CheckNotNull(drawable, "Invalid Pointer 'drawable' from GetDrawable()"))
		return;

	auto* volume = GetVolume();
	if (!CheckNotNull(volume, "Invalid Pointer 'volume' from GetVolume()"))
		return;

	volume->Update(GetPosition());
}

void DynamicCollectable::OnCollisionEnter(IGameObject* obj)
{
}

void DynamicCollectable::OnCollisionStay(IGameObject* obj)
{

}

void DynamicCollectable::OnCollisionExit(IGameObject* obj)
{

}

void DynamicCollectable::ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition)
{

}