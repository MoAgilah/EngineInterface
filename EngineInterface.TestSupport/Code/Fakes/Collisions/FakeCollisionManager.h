#pragma once

#include <Engine/Interface/Collisions/ICollisionManager.h>

class FakeCollisionManager : public ICollisionManager
{
public:
	using ICollisionManager::ICollisionManager;
	using ICollisionManager::CanCollideWithTile;


	FakeCollisionManager(std::shared_ptr<IGrid> grid)
		: ICollisionManager(std::move(grid))
	{}

protected:

	void ObjectToObjectResolution(IGameObject* obj1, IGameObject* obj2) override
	{
		objectToObjectCalls++;
	}

	void DynamicObjectToObjectResolution(IDynamicGameObject* obj1, IGameObject* obj2, float time) override
	{
		dynamicToObjectCalls++;
	}

	void DynamicObjectToDynamicObjectResolution(IDynamicGameObject* obj1, IDynamicGameObject* obj2, float time) override
	{
		dynamicToDynamicCalls++;
	}

public:

	int objectToObjectCalls = 0;
	int dynamicToObjectCalls = 0;
	int dynamicToDynamicCalls = 0;
};
