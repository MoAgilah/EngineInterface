#include "ICollisionManager.h"

#include "IBoundingVolume.h"
#include "IGrid.h"
#include "ITile.h"
#include "../Scene/IGameObject.h"
#include "../Renderer/IRenderable.h"
#include "../../../Utilities/Utils.h"
#include "../../../Utilities/Vector.h"
#include <algorithm>
#include <ranges>
#include <utility>

std::vector<std::type_index> ICollisionManager::s_canCollideWithTile = {};

ICollisionManager::ICollisionManager(std::shared_ptr<IGrid> grid)
	: m_grid(std::move(grid))
{
	if (m_grid)
	{
		for (auto& tile : m_grid->GetGrid())
		{
			if (tile->GetType() != Types::EMPTY)
				m_tiles.push_back(tile.get());
		}
	}
}

void ICollisionManager::ProcessCollisions(IGameObject* obj)
{
	ENSURE_VALID(obj);

	if (CanCollideWithTile(obj->GetTypeIndex()))
	{
		if (auto* dynObj = dynamic_cast<IDynamicGameObject*>(obj))
			DynamicObjectToTileCollisions(dynObj);
	}

	for (auto collidable : m_collidables)
	{
		if (!collidable || !collidable->GetActive())
			continue;

		if (obj->GetObjectNum() == collidable->GetObjectNum())
			continue;

		ObjectToObjectCollisions(obj, collidable);
	}
}

void ICollisionManager::Render(IRenderer* renderer)
{
	ENSURE_VALID(renderer);

	if (m_grid)
		m_grid->Render(renderer);
}

void ICollisionManager::RemoveCollidable(IGameObject* obj)
{
	ENSURE_VALID(obj);

	m_collidables.erase(
		std::remove_if(m_collidables.begin(), m_collidables.end(),
			[obj](IGameObject* ptr) {
				return ptr == obj;
			}),
		m_collidables.end());
}

void ICollisionManager::RemoveLastAdded()
{
	if (!m_collidables.empty())
		m_collidables.pop_back();
}

IGameObject* ICollisionManager::GetLastAdded()
{
	return m_collidables.empty() ? nullptr : m_collidables.back();
}

ITile* ICollisionManager::GetTile(int x, int y)
{
	return m_grid->GetTile(x, y);
}

std::vector<ITile*> ICollisionManager::GetGrid()
{
	if (m_grid)
	{
		auto stripShared = [](const std::vector<std::shared_ptr<ITile>>& src) {
			std::vector<ITile*> result;
			result.reserve(src.size());
			std::transform(src.begin(), src.end(), std::back_inserter(result),
				[](const std::shared_ptr<ITile>& sp) { return sp.get(); });
			return result;
			};

		return stripShared(m_grid->GetGrid());
	}

	return {};
}

std::vector<IGameObject*> ICollisionManager::GetCollidables()
{
	return m_collidables;
}

Direction ICollisionManager::GetCollisionDirection(const Vector2f& sep, const Vector2f& v1, const Vector2f& v2)
{
	constexpr float EPS = 1e-5f;
	const float ax = std::fabs(sep.x), ay = std::fabs(sep.y);

	if (ax > ay + EPS)  return (sep.x > 0.0f) ? Direction::RDIR : Direction::LDIR;
	if (ay > ax + EPS)  return (sep.y > 0.0f) ? Direction::UDIR : Direction::DDIR;

	// tie / tiny MTV: use relative velocity
	const float rx = v1.x - v2.x, ry = v1.y - v2.y;
	if (std::fabs(rx) >= std::fabs(ry))
		return (rx > 0.0f) ? Direction::RDIR : Direction::LDIR;
	else
		return (ry > 0.0f) ? Direction::UDIR : Direction::DDIR;
}

bool ICollisionManager::CanCollideWithTile(std::type_index typeIndex)
{
	return std::find(s_canCollideWithTile.begin(),
		s_canCollideWithTile.end(),
		typeIndex) != s_canCollideWithTile.end();
}

void ICollisionManager::SortCollidedTiles(std::vector<ITile*> collidedWith)
{
	std::ranges::sort(collidedWith, [](const auto& a, const auto& b)
		{
			if (a->GetColNum() == b->GetColNum())
				return a->GetRowNum() < b->GetRowNum();

			return a->GetColNum() > b->GetColNum();
		});
}

void ICollisionManager::DynamicObjectToTileCollisions(IDynamicGameObject* obj)
{
	ENSURE_VALID(obj);

	std::vector<ITile*> collidedWith;
	for (const auto& tile : m_tiles)
	{
		if (!tile->GetActive())
			continue;

		float tFirst;
		float tLast;

		if (tile->Intersects(obj, tFirst, tLast))
			collidedWith.push_back(tile);
	}

	if (!collidedWith.empty())
	{
		if (obj->GetDirection())
			SortCollidedTiles(collidedWith);

		for (const auto& tile : collidedWith)
		{
			float tFirst;
			float tLast;

			if (tile->Intersects(obj, tFirst, tLast))
				tile->ResolveCollision(obj, tFirst, tLast);
		}
	}
	else
	{
		obj->SetOnGround(false);
		obj->SetOnSlope(false);
	}
}

void ICollisionManager::ObjectToObjectCollisions(IGameObject* obj1, IGameObject* obj2)
{
	ENSURE_VALID(obj1);
	ENSURE_VALID(obj2);

	const bool isDyn1 = obj1->IsDynamicObject();
	const bool isDyn2 = obj2->IsDynamicObject();

	if (isDyn1 && isDyn2)
	{
		DynamicObjectToDynamicObjectCollisions(
			dynamic_cast<IDynamicGameObject*>(obj1),
			dynamic_cast<IDynamicGameObject*>(obj2));
	}
	else if (isDyn1)
	{
		DynamicObjectToObjectCollisions(dynamic_cast<IDynamicGameObject*>(obj1), obj2);
	}
	else if (isDyn2)
	{
		DynamicObjectToObjectCollisions(dynamic_cast<IDynamicGameObject*>(obj2), obj1);
	}
	else
	{
		if (obj1->Intersects(obj2))
			ObjectToObjectResolution(obj1, obj2);
	}
}

void ICollisionManager::DynamicObjectToObjectCollisions(IDynamicGameObject* obj1, IGameObject* obj2)
{
	ENSURE_VALID(obj1);
	ENSURE_VALID(obj2);

	float tFirst, tLast;
	if (obj2->Intersects(obj1, tFirst, tLast))
		DynamicObjectToObjectResolution(obj1, obj2, tFirst);
}

void ICollisionManager::DynamicObjectToDynamicObjectCollisions(IDynamicGameObject* obj1, IDynamicGameObject* obj2)
{
	ENSURE_VALID(obj1);
	ENSURE_VALID(obj2);

	float tFirst, tLast;
	if (obj1->Intersects(obj2, tFirst, tLast))
		DynamicObjectToDynamicObjectResolution(obj1, obj2, tFirst);
}

void ICollisionManager::ObjectToObjectResolution(IGameObject* obj1, IGameObject* obj2)
{
	// Custom logic placeholder
}

void ICollisionManager::DynamicObjectToObjectResolution(IDynamicGameObject* obj1, IGameObject* obj2, float time)
{
	// Custom logic placeholder
}

void ICollisionManager::DynamicObjectToDynamicObjectResolution(IDynamicGameObject* obj1, IDynamicGameObject* obj2, float time)
{
	// Custom logic placeholder
}

Direction ICollisionManager::GetFacingDirection(IDynamicGameObject* obj)
{
	const Vector2f& currentVel = obj->GetVelocity();

	Direction currentDir = Direction::DDIR;

	if (currentVel.x != 0.f || currentVel.y != 0.f)
	{
		float vxa = std::abs(currentVel.x);
		float vya = std::abs(currentVel.y);

		if (vxa > vya)
		{
			currentDir = (currentVel.x < 0) ?
				Direction::LDIR : Direction::RDIR;
		}
		else
		{
			currentDir = (currentVel.y < 0) ?
				Direction::UDIR : Direction::DDIR;
		}
	}

	return currentDir;
}