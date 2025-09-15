#pragma once

#include "../Drawables/IDrawable.h"
#include "../Collisions/IBoundingVolume.h"

struct SpawnData
{
	bool initialDir = true;
	Vector2f initialPos;
};

struct AnimationData
{
	int rows;
	int cols;
	bool symmetrical;
	float animationSpeed;
};

class IDynamicGameObject;

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	std::string GetID() { return m_typeID; }
	int GetObjectNum() const { return m_objectID; }
	virtual bool IsDynamicObject() { return false; }

	virtual void Update(float deltaTime) = 0;
	virtual void Render(IRenderer* renderer) = 0;
	virtual bool Intersects(IGameObject* obj) = 0;
	virtual bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) = 0;
	virtual void OnCollisionEnter(IGameObject* obj) = 0;
	virtual void OnCollisionStay(IGameObject* obj) = 0;
	virtual void OnCollisionExit(IGameObject* obj) = 0;
	virtual void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) = 0;
	virtual void Reset() = 0;

	virtual IDrawable* GetDrawable() = 0;
	virtual IBoundingVolume* GetVolume() = 0;

	virtual bool GetActive() const { return m_active; }
	void SetActive(bool act) { m_active = act; }

	virtual bool GetDirection() const { return m_direction; }
	virtual void SetDirection(bool dir) { m_direction = dir; }

protected:

	int m_objectID = 0;
	static int s_objectNum;
	std::string m_typeID;
	bool m_active = false;
	bool m_direction = true;
};

class IDynamicGameObject : public virtual IGameObject, public IMoveableWithVelocity
{
public:
	virtual ~IDynamicGameObject() = default;

	bool IsDynamicObject() override { return true; }

	virtual bool GetOnGround() const { return m_onGround; }
	virtual void SetOnGround(bool grnd) { m_onGround = grnd; }

	virtual bool GetOnSlope() const { return m_onSlope; }
	virtual void SetOnSlope(bool slp);

	bool GetShouldSlideLeft() const { return m_shouldSlideLeft; }
	void SetShouldSlideLeft(bool left);

	bool GetSlideLeft() const { return m_slideLeft; }
	void SetSlideLeft(bool left);

	bool GetShouldSlideRight() const { return m_shouldSlideRight; }
	void SetShouldSlideRight(bool right);

	bool GetSlideRight() const { return m_slideRight; }
	void SetSlideRight(bool right);

	Direction GetFacingDirection();

protected:

	bool m_onGround = false;
	bool m_onSlope = false;
	bool m_slideLeft = false;
	bool m_slideRight = false;
	bool m_shouldSlideLeft = false;
	bool m_shouldSlideRight = false;
};