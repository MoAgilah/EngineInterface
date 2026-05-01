#pragma once

#include <Engine/Interface/Collisions/ICollisionManager.h>

class FakeCollisionManager : public ICollisionManager
{
public:
	FakeCollisionManager(std::shared_ptr<IGrid> grid)
		: ICollisionManager(std::move(grid))
	{}

protected:

	void ObjectToObjectResolution(IGameObject* obj1, IGameObject* obj2) override
	{
		objectToObjectCalled = true;
	}

	void DynamicObjectToObjectResolution(IDynamicGameObject* obj1, IGameObject* obj2, float time) override
	{
		dynamicToObjectCalled = true;
	}

	void DynamicObjectToDynamicObjectResolution(IDynamicGameObject* obj1, IDynamicGameObject* obj2, float time) override
	{
		dynamictoDynamicCalled = true;
	}

public:

	bool objectToObjectCalled = false;
	bool dynamicToObjectCalled = false;
	bool dynamictoDynamicCalled = false;
};
