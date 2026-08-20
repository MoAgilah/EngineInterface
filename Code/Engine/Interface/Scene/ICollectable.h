#pragma once

#include "IGameObject.h"
#include "../../../Utilities/Guards.h"

class ICollectable
{
public:
	virtual ~ICollectable() = default;

	void SetCollected() { m_collected = true; }
	bool GetCollected() const { return m_collected; }

	virtual void Collect(IGameObject* obj) = 0;

protected:

	virtual void Init(const Vector2f& initPos) = 0;

	void InitCollectable(IGameObject* obj, const Vector2f& initPos)
	{
		if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
			return;

		obj->SetInitialActive(true);
		obj->SetActive(obj->GetInitialActive());

		obj->SetInitialDirection(true);
		obj->SetDirection(obj->GetInitialDirection());

		obj->SetInitialPosition(initPos);
		obj->SetPosition(obj->GetInitialPosition());

		auto vol = obj->GetVolume();

		if (!CheckNotNull(vol, "Invalid Pointer 'vol'"))
			return;

		vol->Update(obj->GetPosition());
	}

	bool IsCollectableActive(bool baseActive) const
	{
		return !m_collected && baseActive;
	}

	bool m_collected = false;
};
