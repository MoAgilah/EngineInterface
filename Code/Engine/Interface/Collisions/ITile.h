#pragma once

#include "../Collisions/IBoundingVolume.h"
#include "../Drawables/IShape.h"
#include "../Scene/IGameObject.h"
#include "../UI/IText.h"
#include "../../../Utilities/Colour.h"
#include "../../../Utilities/Utils.h"
#include <memory>
#include <string>
#include <vector>
#include <format>

enum class Types
{
	EMPTY, GRND, WALL, DIAGU, DIAGD, LCRN, RCRN, OWAY
};

class ITile
{
public:
	ITile() = default;
	ITile(int x, int y, std::shared_ptr<IBoundingBox> aabb, std::shared_ptr<IDrawable> text, std::shared_ptr<ITriangleShape> slope)
		: m_text(std::move(text)), m_slope(std::move(slope)), m_aabb(std::move(aabb))
	{
		m_colNum = x;
		m_rowNum = y;

		m_id = std::format("{},{}", m_colNum, m_rowNum);

		ENSURE_VALID(m_aabb);
	}
	virtual ~ITile() {};

	virtual void Render(IRenderer* renderer) = 0;

	bool Intersects(IDynamicGameObject* obj)
	{
		ENSURE_VALID_RET(m_aabb, false);
		return m_aabb->Intersects(obj->GetVolume());
	}
	virtual void ResolveCollision(IDynamicGameObject* obj) = 0;

	std::string_view GetID() const { return m_id; }

	int GetRowNum() const { return m_rowNum; }
	int GetColNum() const { return m_colNum; }

	void SetType(int type) { m_type = (Types)type; };
	Types GetType() const { return m_type; }

	bool GetActive() const { return m_visible; }
	void SetActive(bool vis) { m_visible = vis; }

	virtual void SetPosition(const Vector2f& pos) = 0;
	Vector2f GetPosition()
	{
		ENSURE_VALID_RET(m_aabb, Vector2f());
		return m_aabb->GetPosition();
	}

	void SetOrigin(const Vector2f& origin)
	{
		if (m_aabb)
			m_aabb->SetOrigin(origin);
	}

	Vector2f GetOrigin()
	{
		ENSURE_VALID_RET(m_aabb, Vector2f());
		return m_aabb->GetOrigin();
	}

	IBoundingBox* GetBoundingBox()
	{
		ENSURE_VALID_RET(m_aabb, nullptr);
		return m_aabb.get();
	}

	virtual void SetSlope(std::shared_ptr<ITriangleShape> slope)
	{
		ENSURE_VALID(slope);
		m_slope = std::move(slope);
	}

	virtual Linef GetSlope(int bgn, int end)
	{
		ENSURE_VALID_RET(m_slope, Linef());
		return m_slope->GetLine(bgn, end);
	}

	Linef GetEdge() const { return m_edge; }

	float GetTileHeight()
	{
		ENSURE_VALID_RET(m_aabb, float());
		return m_aabb->GetExtents().y * 2;
	}
	virtual void SetFillColour(Colour col) = 0;
	virtual void SetOutlineColour(Colour col) = 0;

protected:

	Vector2f GetSeperationVector(IDynamicGameObject* obj)
	{
		ENSURE_VALID_RET(m_aabb, Vector2f());
		return m_aabb->GetSeparationVector(obj->GetVolume());
	}

	virtual void ResolveObjectToBoxTop(IDynamicGameObject* obj) = 0;
	virtual void ResolveObjectToBoxBottom(IDynamicGameObject* obj) = 0;
	virtual void ResolveObjectToBoxHorizontally(IDynamicGameObject* obj) = 0;
	virtual bool ResolveObjectToSlopeTop(IDynamicGameObject* obj) = 0;
	virtual bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end) = 0;
	virtual bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end) = 0;
	virtual void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) = 0;

	int m_colNum = -1;
	int m_rowNum = -1;
	bool m_visible = false;
	bool m_hasFont = false;
	Types m_type = Types::EMPTY;
	std::string m_id;
	Linef m_edge;
	std::shared_ptr<IDrawable> m_text;
	std::shared_ptr<ITriangleShape> m_slope;
	std::shared_ptr<IBoundingBox> m_aabb;
};