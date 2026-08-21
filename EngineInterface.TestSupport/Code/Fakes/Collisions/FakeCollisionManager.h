#pragma once

#include <Engine/Interface/Collisions/ICollisionManager.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class FakeCollisionManager : public ICollisionManager
{
public:
	using ICollisionManager::ICollisionManager;
	using ICollisionManager::CanCollideWithTile;


	FakeCollisionManager(std::shared_ptr<IGrid> grid)
		: ICollisionManager(std::move(grid))
	{}

	void Render(IRenderer* renderer) override
	{
		renderCalled = true;

		if (renderLog)
			renderLog->push_back(renderId);
	}

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

	bool renderCalled = false;

	std::vector<std::string>* renderLog = nullptr;
	std::string renderId = "collision-manager";
};
