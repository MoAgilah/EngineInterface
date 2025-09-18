#pragma once

class IRenderer;

#include "../../../Utilities/Colour.h"
#include "../../../Utilities/Vector.h"
#include "../../../Utilities/Line.h"
#include <array>

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void Update(const Vector2f& pos) = 0;
	virtual void Render(IRenderer* renderer) = 0;

	const Vector2f& GetCenter() { return m_center; }
	void SetCenter(const Vector2f& center) { m_center = center; }

	virtual void SetRotation(float rotation) = 0;

	virtual Colour GetFillColour() = 0;
	virtual void SetFillColour(const Colour& col) = 0;

	virtual Colour GetOutlineColour() = 0;
	virtual void SetOutlineColour(const Colour& col) = 0;

	virtual float GetOutlineThickness() = 0;
	virtual void SetOutlineThickness(float scale) = 0;

protected:

	Vector2f m_center;
};

class IBoxShape
{
public:
	virtual ~IBoxShape() = default;

	virtual void Render(IRenderer* renderer) = 0;

	virtual Vector2f GetSize() = 0;
	virtual void SetSize(const Vector2f& size) = 0;
};

class ICircleShape
{
public:
	virtual ~ICircleShape() = default;

	virtual void Render(IRenderer* renderer) = 0;

	virtual float GetRadius() = 0;
	virtual void SetRadius(float radius) = 0;
};

class ICapsuleShape
{
public:
	virtual ~ICapsuleShape() = default;

	virtual void Render(IRenderer* renderer) = 0;

	virtual float GetRadius() const { return m_radius; }
	virtual void SetRadius(float radius) { m_radius = radius; }

	virtual float GetLength() const { return m_length; }
	virtual void SetLength(float length) { m_length = length; }

	virtual float GetAngle() const { return m_angle; }
	virtual void SetAngle(float angle) { m_angle = angle; }

	virtual const Linef& GetSegment() const { return m_segment; }
	virtual void SetSegment(const Linef& segment) { m_segment = segment; }

protected:

	float m_angle = 0.f;
	float m_radius = 0.f;
	float m_length = 0.f;
	Linef m_segment;
};

class ITriangleShape
{
public:
	virtual ~ITriangleShape() = default;

	virtual void Render(IRenderer* renderer) = 0;

	virtual Vector2f GetPoint(int idx) = 0;
	virtual Linef GetLine(int start, int end) = 0;

	// Returns the three points of the triangle
	virtual std::array<Vector2f, 3> GetPoints() const = 0;

	// Sets the three points of the triangle
	virtual void SetPoints(const std::array<Vector2f, 3>& points) = 0;
};
