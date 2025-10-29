#pragma once

#include "../Collisions/IBoundingVolume.h"
#include "../Drawables/IShape.h"
#include "../Scene/IGameObject.h"
#include "../UI/IText.h"
#include "../../../Utilities/Colour.h"
#include "../../../Utilities/Utils.h"
#include <algorithm>
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
	ITile(int x, int y, std::shared_ptr<IBoundingBox> aabb, std::shared_ptr<IDrawable> text, std::shared_ptr<ITriangleShape> slope);
	virtual ~ITile() = default;

	virtual void Render(IRenderer* renderer) = 0;

	bool Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast);

	virtual void ResolveCollision(IDynamicGameObject* obj, float tFirst, float tLast) = 0;

	std::string_view GetID() const { return m_id; }

	int GetRowNum() const { return m_rowNum; }
	int GetColNum() const { return m_colNum; }

	void SetType(int type) { m_type = (Types)type; };
	Types GetType() const { return m_type; }

	bool GetActive() const { return m_visible; }
	void SetActive(bool vis) { m_visible = vis; }

	virtual void SetPosition(const Vector2f& pos) = 0;
	Vector2f GetPosition();

	void SetOrigin(const Vector2f& origin);

	Vector2f GetOrigin();

	IBoundingBox* GetBoundingBox();

	virtual void SetSlope(std::shared_ptr<ITriangleShape> slope);

	virtual Linef GetSlope(int bgn, int end);

	Linef GetEdge() const { return m_edge; }

	float GetTileHeight();

	virtual void SetFillColour(Colour col) = 0;
	virtual void SetOutlineColour(Colour col) = 0;

protected:

	Vector2f GetSeperationVector(IDynamicGameObject* obj);

	void ResolveToObjectToTileSide(IDynamicGameObject* obj, Side tileSide, float time);

	virtual void ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast);

	virtual void ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast);

	virtual void ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast);

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