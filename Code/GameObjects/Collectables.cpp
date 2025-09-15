#include "Collectables.h"

#include "../Engine/Core/GameManager.h"

StaticCollectable::StaticCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos)
	: GameObject(std::move(drawable), std::move(volume))
{
	Init(initPos);
}

void StaticCollectable::Init(const Vector2f& initPos)
{
	SetInitialDirection(true);
	SetDirection(GetInitialDirection());
	SetInitialPosition(initPos);
	SetPosition(GetInitialPosition());
	GetVolume()->Update(GetPosition());
}

DynamicCollectable::DynamicCollectable(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos)
	: DynamicGameObject(std::move(drawable), std::move(volume))
{
	Init(initPos);
}

void DynamicCollectable::Init(const Vector2f& initPos)
{
	SetInitialDirection(true);
	SetDirection(GetInitialDirection());
	SetInitialPosition(initPos);
	SetPosition(GetInitialPosition());
	GetVolume()->Update(GetPosition());
}
