#include "ITile.h"

#include "../../../Utilities/Guards.h"

ITile::ITile(int x, int y, std::shared_ptr<IBoundingBox> aabb, std::shared_ptr<IDrawable> text, std::shared_ptr<ITriangleShape> slope)
	: m_text(std::move(text)), m_slope(std::move(slope)), m_aabb(std::move(aabb))
{
	m_colNum = x;
	m_rowNum = y;

	m_id = std::format("{},{}", m_colNum, m_rowNum);

	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
	{
		throw std::invalid_argument("ITile requires a valid BoundingBox");
	}
}

bool ITile::Intersects(IDynamicGameObject* obj, float& tFirst, float& tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return false;

	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return false;

	return m_aabb->IntersectsMoving(obj->GetVolume(), Vector2f(0, 0), obj->GetVelocity(), tFirst, tLast);
}

Vector2f ITile::GetPosition()
{
	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return Vector2f();

	return m_aabb->GetPosition();
}

void ITile::SetOrigin(const Vector2f& origin)
{
	if (CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		m_aabb->SetOrigin(origin);
}

Vector2f ITile::GetOrigin()
{
	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return Vector2f();

	return m_aabb->GetOrigin();
}

IBoundingBox* ITile::GetBoundingBox()
{
	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return nullptr;

	return m_aabb.get();
}

void ITile::SetSlope(std::shared_ptr<ITriangleShape> slope)
{
	if (!CheckNotNull(slope.get(), "Invalid Pointer 'slope'"))
		return;

	m_slope = std::move(slope);
}

Line2f ITile::GetSlope(int bgn, int end)
{
	if (!CheckNotNull(m_slope.get(), "Invalid Pointer 'slope'"))
		return Line2f();

	return m_slope->GetLine(bgn, end);
}

float ITile::GetTileWidth()
{
	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return float();

	return m_aabb->GetExtents().x * 2.f;
}

float ITile::GetTileHeight()
{
	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return float();

	return m_aabb->GetExtents().y * 2.f;
}

Vector2f ITile::GetSeparationVector(IDynamicGameObject* obj)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return Vector2f();

	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return Vector2f();

	if (!CheckNotNull(obj->GetVolume(), "Invalid Pointer 'obj->GetVolume()'"))
		return Vector2f();

	return m_aabb->GetSeparationVector(obj->GetVolume());
}

void ITile::ResolveToObjectToTileSide(IDynamicGameObject* obj, Side tileSide, float time)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return;

	if (!CheckNotNull(m_aabb.get(), "Invalid Pointer 'm_aabb'"))
		return;

	if (!CheckNotNull(obj->GetVolume(), "Invalid Pointer 'obj->GetVolume()'"))
		return;

	const Vector2f vel = obj->GetVelocity();
	const float remainingTime = std::clamp(1.0f - time, 0.0f, 1.0f);

	// rewind using velocity, not separation
	obj->Move(
		-vel.x * remainingTime,
		-vel.y * remainingTime
	);

	// snap using volume geometry
	const Line2f tileEdge = m_aabb->GetSide(tileSide);
	const Vector2f objOppPt = obj->GetVolume()->GetPoint(OppositeSide(tileSide));

	Vector2f snap(0.f, 0.f);

	if (tileSide == Side::Top || tileSide == Side::Bottom)
		snap.y = tileEdge.start.y - objOppPt.y;
	else
		snap.x = tileEdge.start.x - objOppPt.x;

	obj->Move(snap);
}

void ITile::ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return;

	ResolveToObjectToTileSide(obj, Side::Top, tFirst);

	auto v = obj->GetVelocity();
	if (v.y > 0.f)
		v.y = 0.f;
	obj->SetVelocity(v);

	obj->SetOnGround(true);
	obj->SetOnSlope(false);
}

void ITile::ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return;

	ResolveToObjectToTileSide(obj, Side::Bottom, tFirst);

	auto v = obj->GetVelocity();
	if (v.y < 0.f)
		v.y = 0.f;
	obj->SetVelocity(v);
}

void ITile::ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast)
{
	if (!CheckNotNull(obj, "Invalid Pointer 'obj'"))
		return;

	const Vector2f sep = GetSeparationVector(obj);

	if (sep.x > 0.f)
		ResolveToObjectToTileSide(obj, Side::Right, tFirst);
	else
		ResolveToObjectToTileSide(obj, Side::Left, tFirst);

	// kill horizontal velocity
	auto v = obj->GetVelocity();
	v.x = 0.f;
	obj->SetVelocity(v);
}