#include "ITile.h"

ITile::ITile(int x, int y, std::shared_ptr<IBoundingBox> aabb, std::shared_ptr<IDrawable> text, std::shared_ptr<ITriangleShape> slope)
	: m_text(std::move(text)), m_slope(std::move(slope)), m_aabb(std::move(aabb))
{
	m_colNum = x;
	m_rowNum = y;

	m_id = std::format("{},{}", m_colNum, m_rowNum);

	ENSURE_VALID(m_aabb);
}

bool ITile::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	ENSURE_VALID_RET(obj, false);
	ENSURE_VALID_RET(m_aabb, false);
	return m_aabb->IntersectsMoving(obj->GetVolume(), Vector2f(0, 0), obj->GetVelocity(), tFirst, tLast);
}

Vector2f ITile::GetPosition()
{
	ENSURE_VALID_RET(m_aabb, Vector2f());
	return m_aabb->GetPosition();
}

void ITile::SetOrigin(const Vector2f& origin)
{
	if (m_aabb)
		m_aabb->SetOrigin(origin);
}

Vector2f ITile::GetOrigin()
{
	ENSURE_VALID_RET(m_aabb, Vector2f());
	return m_aabb->GetOrigin();
}

IBoundingBox* ITile::GetBoundingBox()
{
	ENSURE_VALID_RET(m_aabb, nullptr);
	return m_aabb.get();
}

void ITile::SetSlope(std::shared_ptr<ITriangleShape> slope)
{
	ENSURE_VALID(slope);
	m_slope = std::move(slope);
}

Linef ITile::GetSlope(int bgn, int end)
{
	ENSURE_VALID_RET(m_slope, Linef());
	return m_slope->GetLine(bgn, end);
}

float ITile::GetTileWidth()
{
	ENSURE_VALID_RET(m_aabb, float());
	return m_aabb->GetExtents().x;
}

float ITile::GetTileHeight()
{
	ENSURE_VALID_RET(m_aabb, float());
	return m_aabb->GetExtents().y;
}

Vector2f ITile::GetSeperationVector(IDynamicGameObject* obj)
{
	ENSURE_VALID_RET(m_aabb, Vector2f());
	return m_aabb->GetSeparationVector(obj->GetVolume());
}

void ITile::ResolveToObjectToTileSide(IDynamicGameObject* obj, Side tileSide, float time)
{
	ENSURE_VALID(obj);
	ENSURE_VALID(m_aabb);
	ENSURE_VALID(obj->GetVolume());

	const Vector2f sep = GetSeperationVector(obj);
	const float fracAfterTOI = std::clamp(1.0f - time, 0.0f, 1.0f);

	Vector2f rewind(0.f, 0.f);

	switch (tileSide)
	{
	case Side::Left:
		rewind.x = -sep.x * fracAfterTOI;
		break;
	case Side::Right:
		rewind.x = sep.x * fracAfterTOI;
		break;
	case Side::Top:
		rewind.y = -sep.y * fracAfterTOI;
		break;
	case Side::Bottom:
		rewind.y = sep.y * fracAfterTOI;
		break;
	}

	obj->Move(rewind.x, rewind.y);

	const Line tileEdge = m_aabb->GetSide(tileSide);
	const Vector2f objOppPt = obj->GetVolume()->GetPoint(OppositeSide(tileSide));

	Vector2f snap(0.f, 0.f);
	if (tileSide == Side::Top || tileSide == Side::Bottom)
		snap.y = tileEdge.start.y - objOppPt.y;
	else
		snap.x = tileEdge.start.x - objOppPt.x;

	obj->Move(snap.x, snap.y);
}

void ITile::ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	ResolveToObjectToTileSide(obj, Side::Top, tFirst);

	obj->SetOnGround(true);
	obj->SetOnSlope(false);
}

void ITile::ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast)
{
	ResolveToObjectToTileSide(obj, Side::Bottom, tFirst);
}

void ITile::ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast)
{
	ResolveToObjectToTileSide(obj, obj->GetDirection() ? Side::Right : Side::Left, tFirst);
}