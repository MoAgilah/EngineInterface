#pragma once

#include "GameObject.h"
#include "../Engine/Core/Timer.h"

class Box : public GameObject
{
public:
	Box(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, const Vector2f& initPos);
	~Box() override = default;

	void OnCollisionEnter(IGameObject* obj);
	void OnCollisionStay(IGameObject* obj);
	void OnCollisionExit(IGameObject* obj);
	void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition);

	void Reset() override;

	void SetCanHit(bool canHit) { m_canHit = canHit; }
	bool GetCanHit() const { return m_canHit; }
	void SetJustHit(bool justHit) { m_justHit = justHit; }
	bool GetJustHit() const { return m_justHit; }

	void WasJustHit();

private:

	virtual void Init(const Vector2f& initPos);

	bool m_canHit = true;
	bool m_justHit = false;
};