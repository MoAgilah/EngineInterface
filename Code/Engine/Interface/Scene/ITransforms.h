#pragma once

#include "../../../Utilities/Vector.h"

class ITransforms
{
public:
	virtual ~ITransforms() = default;

	virtual void SetPosition(const Vector2f& pos) = 0;
	virtual Vector2f GetPosition() = 0;

	virtual void SetScale(const Vector2f& scl) = 0;
	virtual Vector2f GetScale() = 0;

	virtual Vector2f GetOrigin() = 0;
	virtual void SetOrigin(const Vector2f& pos) = 0;

	virtual Vector2f GetSize() = 0;
	virtual void SetSize(const Vector2f& size) = 0;

protected:

	Vector2f m_scale;
};

class IMoveable
{
public:
	virtual ~IMoveable() = default;

	virtual void Move(float x, float y) = 0;
	virtual void Move(const Vector2f& mov) = 0;
};

// Moveable + velocity
class IMoveableWithVelocity : public IMoveable
{
public:
	virtual ~IMoveableWithVelocity() = default;

	virtual void SetVelocity(const Vector2f& vel) { m_velocity = vel; }
	virtual Vector2f GetVelocity() const { return m_velocity; }

protected:

	Vector2f m_velocity;
};