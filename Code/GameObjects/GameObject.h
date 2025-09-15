#pragma once

#include "../Engine/Interface/Scene/IGameObject.h"

class GameObject : public virtual IGameObject
{
public:
	GameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume);
	virtual ~GameObject();

	void Render(IRenderer* renderer) override;

	bool Intersects(IGameObject* obj) override;

	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) override;

	void Reset() override;

	IDrawable* GetDrawable() override { return m_drawable.get(); }
	IBoundingVolume* GetVolume() override { return m_volume.get(); }

	virtual float GetRestitution() { return m_restitution; }
	virtual void SetRestitution(float restitution) { m_restitution = restitution; }

	Vector2f GetPosition() const { return m_drawable->GetPosition(); }
	void SetPosition(const Vector2f& pos) { m_drawable->SetPosition(pos); }
	void SetPosition(float x, float y) { m_drawable->SetPosition({ x, y }); }
	Vector2f GetOrigin() const { return m_drawable->GetOrigin(); }
	void SetScale(const Vector2f& scale);
	Vector2f GetScale() const { return m_drawable->GetScale(); }

	bool GetInitialDirection() const { return m_spawnData.initialDir; }
	void SetInitialDirection(bool dir) { m_spawnData.initialDir = dir; }
	Vector2f GetInitialPosition() const { return m_spawnData.initialPos; }
	void SetInitialPosition(const Vector2f& pos) { m_spawnData.initialPos = pos; }

protected:


	float m_restitution = 1;
	SpawnData m_spawnData;
	std::shared_ptr<IDrawable> m_drawable;
	std::shared_ptr<IBoundingVolume> m_volume;
};

class DynamicGameObject : public GameObject, public virtual IDynamicGameObject
{
public:
	DynamicGameObject(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume);

	void Render(IRenderer* renderer) override { GameObject::Render(renderer); }

	bool Intersects(IGameObject* obj) override;

	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast) override;

	void Reset() override;

	IDrawable* GetDrawable() override { return GameObject::GetDrawable(); }
	IBoundingVolume* GetVolume() override { return GameObject::GetVolume(); }

	bool IsDynamicObject() override { return IDynamicGameObject::IsDynamicObject(); }

	void SetPrevPosition(Vector2f pos) { m_previousPos = pos; }
	void SetPrevPosition(float x, float y) { m_previousPos = Vector2f(x, y); }
	Vector2f GetPrevPosition() const { return m_previousPos; }

	float GetXVelocity() const { return m_velocity.x; }
	void SetXVelocity(float x) { m_velocity.x = x; }
	void IncrementXVelocity(float x) { m_velocity.x += x; }
	void DecrementXVelocity(float x) { m_velocity.x -= x; }

	float GetYVelocity() const { return m_velocity.y; }
	void SetYVelocity(float y) { m_velocity.y = y; }
	void IncrementYVelocity(float y) { m_velocity.y += y; }
	void DecrementYVelocity(float y) { m_velocity.y -= y; }

protected:

	Vector2f m_previousPos;
};