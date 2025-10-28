#pragma once

#include "../../../Utilities/Vector.h"
#include <limits>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

class IDynamicGameObject;
class IGameObject;
class IGrid;
class ITile;
class IRenderer;
enum class Direction;

class ICollisionManager
{
public:
	ICollisionManager(std::shared_ptr<IGrid> grid);
	virtual ~ICollisionManager() = default;

	void ProcessCollisions(IGameObject* object);
	void Render(IRenderer* renderer);

	void AddCollidable(IGameObject* ngo) { m_collidables.emplace_back(ngo); }
	void RemoveCollidable(IGameObject* ngo);

	void RemoveLastAdded();
	IGameObject* GetLastAdded();

	ITile* GetTile(int x, int y);
	std::vector<ITile*> GetGrid();
	std::vector<IGameObject*> GetCollidables();

	static Direction GetCollisionDirection(const Vector2f& sep, const Vector2f& v1, const Vector2f& v2);

	static std::vector<std::type_index> s_canCollideWithTile;
	inline static const float EPSILON = std::numeric_limits<float>::epsilon() * 100;
	inline static const float BUFFER = 0.01f;

protected:

	bool CanCollideWithTile(std::type_index typeID);
	void SortCollidedTiles(std::vector<ITile*> collidedWith);

	void DynamicObjectToTileCollisions(IDynamicGameObject* obj);

	void ObjectToObjectCollisions(IGameObject* obj1, IGameObject* obj2);

	void DynamicObjectToObjectCollisions(IDynamicGameObject* obj1, IGameObject* obj2);

	void DynamicObjectToDynamicObjectCollisions(IDynamicGameObject* obj1, IDynamicGameObject* obj2);

	virtual void ObjectToObjectResolution(IGameObject* obj1, IGameObject* obj2);

	virtual void DynamicObjectToObjectResolution(IDynamicGameObject* obj1, IGameObject* obj2, float time);

	virtual void DynamicObjectToDynamicObjectResolution(IDynamicGameObject* obj1, IDynamicGameObject* obj2, float time);

	Direction GetFacingDirection(IDynamicGameObject* obj);

	std::shared_ptr<IGrid> m_grid;
	std::vector<ITile*> m_tiles;
	std::vector<IGameObject*> m_collidables;
};